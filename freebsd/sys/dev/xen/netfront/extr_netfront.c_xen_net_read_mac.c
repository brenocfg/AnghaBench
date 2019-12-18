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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  M_XENBUS ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*,char const*) ; 
 char* xenbus_get_node (int /*<<< orphan*/ ) ; 
 char* xenbus_get_otherend_path (int /*<<< orphan*/ ) ; 
 int xs_read (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static int
xen_net_read_mac(device_t dev, uint8_t mac[])
{
	int error, i;
	char *s, *e, *macstr;
	const char *path;

	path = xenbus_get_node(dev);
	error = xs_read(XST_NIL, path, "mac", NULL, (void **) &macstr);
	if (error == ENOENT) {
		/*
		 * Deal with missing mac XenStore nodes on devices with
		 * HVM emulation (the 'ioemu' configuration attribute)
		 * enabled.
		 *
		 * The HVM emulator may execute in a stub device model
		 * domain which lacks the permission, only given to Dom0,
		 * to update the guest's XenStore tree.  For this reason,
		 * the HVM emulator doesn't even attempt to write the
		 * front-side mac node, even when operating in Dom0.
		 * However, there should always be a mac listed in the
		 * backend tree.  Fallback to this version if our query
		 * of the front side XenStore location doesn't find
		 * anything.
		 */
		path = xenbus_get_otherend_path(dev);
		error = xs_read(XST_NIL, path, "mac", NULL, (void **) &macstr);
	}
	if (error != 0) {
		xenbus_dev_fatal(dev, error, "parsing %s/mac", path);
		return (error);
	}

	s = macstr;
	for (i = 0; i < ETHER_ADDR_LEN; i++) {
		mac[i] = strtoul(s, &e, 16);
		if (s == e || (e[0] != ':' && e[0] != 0)) {
			free(macstr, M_XENBUS);
			return (ENOENT);
		}
		s = &e[1];
	}
	free(macstr, M_XENBUS);
	return (0);
}