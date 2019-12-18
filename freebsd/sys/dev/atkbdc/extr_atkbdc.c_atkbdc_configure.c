#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  stdin ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  char ihandle_t ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int ENXIO ; 
 int IO_KBD ; 
 int /*<<< orphan*/  IO_KBDSIZE ; 
 int KBD_DATA_PORT ; 
 int KBD_STATUS_PORT ; 
 scalar_t__ OF_decode_addr (int,int,int*,int*) ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int OF_instance_to_package (char) ; 
 int OF_parent (int) ; 
 int /*<<< orphan*/ * X86_BUS_SPACE_IO ; 
 int /*<<< orphan*/ * atkbdc_bst_store ; 
 int atkbdc_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * atkbdc_softc ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bus_space_read_1 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_subregion (int /*<<< orphan*/ *,scalar_t__,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ sparc64_fake_bustag (int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
atkbdc_configure(void)
{
	bus_space_tag_t tag;
	bus_space_handle_t h0;
	bus_space_handle_t h1;
#if defined(__i386__) || defined(__amd64__)
	volatile int i;
	register_t flags;
#endif
#ifdef __sparc64__
	char name[32];
	phandle_t chosen, node;
	ihandle_t stdin;
	bus_addr_t port0;
	bus_addr_t port1;
	int space;
#else
	int port0;
	int port1;
#endif

	/* XXX: tag should be passed from the caller */
#if defined(__amd64__) || defined(__i386__)
	tag = X86_BUS_SPACE_IO;
#elif defined(__sparc64__)
	tag = &atkbdc_bst_store[0];
#else
#error "define tag!"
#endif

#ifdef __sparc64__
	if ((chosen = OF_finddevice("/chosen")) == -1)
		return 0;
	if (OF_getprop(chosen, "stdin", &stdin, sizeof(stdin)) == -1)
		return 0;
	if ((node = OF_instance_to_package(stdin)) == -1)
		return 0;
	if (OF_getprop(node, "name", name, sizeof(name)) == -1)
		return 0;
	name[sizeof(name) - 1] = '\0';
	if (strcmp(name, "kb_ps2") != 0)
		return 0;
	/*
	 * The stdin handle points to an instance of a PS/2 keyboard
	 * package but we want the 8042 controller, which is the parent
	 * of that keyboard node.
	 */
	if ((node = OF_parent(node)) == 0)
		return 0;
	if (OF_decode_addr(node, 0, &space, &port0) != 0)
		return 0;
	h0 = sparc64_fake_bustag(space, port0, tag);
	bus_space_subregion(tag, h0, KBD_DATA_PORT, 1, &h0);
	if (OF_decode_addr(node, 1, &space, &port1) != 0)
		return 0;
	h1 = sparc64_fake_bustag(space, port1, tag);
	bus_space_subregion(tag, h1, KBD_STATUS_PORT, 1, &h1);
#else
	port0 = IO_KBD;
	resource_int_value("atkbdc", 0, "port", &port0);
	port1 = IO_KBD + KBD_STATUS_PORT;
#ifdef notyet
	bus_space_map(tag, port0, IO_KBDSIZE, 0, &h0);
	bus_space_map(tag, port1, IO_KBDSIZE, 0, &h1);
#else
	h0 = (bus_space_handle_t)port0;
	h1 = (bus_space_handle_t)port1;
#endif
#endif

#if defined(__i386__) || defined(__amd64__)
	/*
	 * Check if we really have AT keyboard controller. Poll status
	 * register until we get "all clear" indication. If no such
	 * indication comes, it probably means that there is no AT
	 * keyboard controller present. Give up in such case. Check relies
	 * on the fact that reading from non-existing in/out port returns
	 * 0xff on i386. May or may not be true on other platforms.
	 */
	flags = intr_disable();
	for (i = 0; i != 65535; i++) {
		if ((bus_space_read_1(tag, h1, 0) & 0x2) == 0)
			break;
	}
	intr_restore(flags);
	if (i == 65535)
                return ENXIO;
#endif

	return atkbdc_setup(atkbdc_softc[0], tag, h0, h1);
}