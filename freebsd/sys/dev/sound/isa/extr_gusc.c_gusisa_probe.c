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
struct sndcard_func {int /*<<< orphan*/  func; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int DV_F_DRQ_MASK ; 
 int DV_F_DUAL_DMA ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SCF_MIDI ; 
 int /*<<< orphan*/  SCF_PCM ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct sndcard_func*) ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 struct sndcard_func* malloc (int,int /*<<< orphan*/ ,int) ; 
 unsigned char port_rd (struct resource*,int) ; 
 int /*<<< orphan*/  port_wr (struct resource*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
gusisa_probe(device_t dev)
{
	device_t child;
	struct resource *res, *res2;
	int base, rid, rid2, s, flags;
	unsigned char val;

	base = isa_get_port(dev);
	flags = device_get_flags(dev);
	rid = 1;
	res = bus_alloc_resource(dev, SYS_RES_IOPORT, &rid, base + 0x100,
				 base + 0x107, 8, RF_ACTIVE);

	if (res == NULL)
		return ENXIO;

	res2 = NULL;

	/*
	 * Check for the presence of some GUS card.  Reset the card,
	 * then see if we can access the memory on it.
	 */

	port_wr(res, 3, 0x4c);
	port_wr(res, 5, 0);
	DELAY(30 * 1000);

	port_wr(res, 3, 0x4c);
	port_wr(res, 5, 1);
	DELAY(30 * 1000);

	s = splhigh();

	/* Write to DRAM.  */

	port_wr(res, 3, 0x43);		/* Register select */
	port_wr(res, 4, 0);		/* Low addr */
	port_wr(res, 5, 0);		/* Med addr */

	port_wr(res, 3, 0x44);		/* Register select */
	port_wr(res, 4, 0);		/* High addr */
	port_wr(res, 7, 0x55);		/* DRAM */

	/* Read from DRAM.  */

	port_wr(res, 3, 0x43);		/* Register select */
	port_wr(res, 4, 0);		/* Low addr */
	port_wr(res, 5, 0);		/* Med addr */

	port_wr(res, 3, 0x44);		/* Register select */
	port_wr(res, 4, 0);		/* High addr */
	val = port_rd(res, 7);		/* DRAM */

	splx(s);

	if (val != 0x55)
		goto fail;

	rid2 = 0;
	res2 = bus_alloc_resource(dev, SYS_RES_IOPORT, &rid2, base, base, 1,
				  RF_ACTIVE);

	if (res2 == NULL)
		goto fail;

	s = splhigh();
	port_wr(res2, 0x0f, 0x20);
	val = port_rd(res2, 0x0f);
	splx(s);

	if (val == 0xff || (val & 0x06) == 0)
		val = 0;
	else {
		val = port_rd(res2, 0x506);	/* XXX Out of range.  */
		if (val == 0xff)
			val = 0;
	}

	bus_release_resource(dev, SYS_RES_IOPORT, rid2, res2);
	bus_release_resource(dev, SYS_RES_IOPORT, rid, res);

	if (val >= 10) {
		struct sndcard_func *func;

		/* Looks like a GUS MAX.  Set the rest of the resources.  */

		bus_set_resource(dev, SYS_RES_IOPORT, 2, base + 0x10c, 8);

		if (flags & DV_F_DUAL_DMA)
			bus_set_resource(dev, SYS_RES_DRQ, 1,
					 flags & DV_F_DRQ_MASK, 1);

		/* We can support the CS4231 and MIDI devices.  */

		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL)
			return ENOMEM;
		func->func = SCF_MIDI;
		child = device_add_child(dev, "midi", -1);
		device_set_ivars(child, func);

		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL)
			printf("xxx: gus pcm not attached, out of memory\n");
		else {
			func->func = SCF_PCM;
			child = device_add_child(dev, "pcm", -1);
			device_set_ivars(child, func);
		}
		device_set_desc(dev, "Gravis UltraSound MAX");
		return 0;
	} else {

		/*
		 * TODO: Support even older GUS cards.  MIDI should work on
		 * all models.
		 */
		return ENXIO;
	}

fail:
	bus_release_resource(dev, SYS_RES_IOPORT, rid, res);
	return ENXIO;
}