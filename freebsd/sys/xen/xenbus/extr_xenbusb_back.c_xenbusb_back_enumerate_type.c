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
typedef  size_t u_int ;
struct xenbusb_softc {int /*<<< orphan*/  xbs_node; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const**,int /*<<< orphan*/ ) ; 
 char const* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  xenbusb_add_device (int /*<<< orphan*/ ,char const*,char const*) ; 
 int xs_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t*,char const***) ; 
 struct sbuf* xs_join (char const*,char const*) ; 

__attribute__((used)) static int
xenbusb_back_enumerate_type(device_t dev, const char *type)
{
	struct xenbusb_softc *xbs;
	const char **vms;
	u_int vm_idx;
	u_int vm_count;
	int error;

	xbs = device_get_softc(dev);
	error = xs_directory(XST_NIL, xbs->xbs_node, type, &vm_count, &vms);
	if (error)
		return (error);
	for (vm_idx = 0; vm_idx < vm_count; vm_idx++) {
		struct sbuf *vm_path;
		const char *vm;
		const char **devs;
		u_int dev_idx;
		u_int dev_count;

		vm = vms[vm_idx];

		vm_path = xs_join(type, vm);
		error = xs_directory(XST_NIL, xbs->xbs_node, sbuf_data(vm_path),
		    &dev_count, &devs);
		sbuf_delete(vm_path);
		if (error)
			break;

		for (dev_idx = 0; dev_idx < dev_count; dev_idx++) {
			const char *dev_num;
			struct sbuf *id;
			
			dev_num = devs[dev_idx];
			id = xs_join(vm, dev_num);
			xenbusb_add_device(dev, type, sbuf_data(id));
			sbuf_delete(id);
		}
		free(devs, M_XENSTORE);
	}

	free(vms, M_XENSTORE);

	return (0);
}