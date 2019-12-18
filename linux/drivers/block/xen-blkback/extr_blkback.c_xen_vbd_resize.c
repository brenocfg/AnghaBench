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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {unsigned long long state; int /*<<< orphan*/  nodename; } ;
struct xen_vbd {unsigned long long size; int /*<<< orphan*/  pdevice; } ;
struct xen_blkif {int /*<<< orphan*/  domid; int /*<<< orphan*/  be; struct xen_vbd vbd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long long,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 unsigned long long vbd_sz (struct xen_vbd*) ; 
 struct xenbus_device* xen_blkbk_xenbus (int /*<<< orphan*/ ) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,unsigned long long) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 

__attribute__((used)) static void xen_vbd_resize(struct xen_blkif *blkif)
{
	struct xen_vbd *vbd = &blkif->vbd;
	struct xenbus_transaction xbt;
	int err;
	struct xenbus_device *dev = xen_blkbk_xenbus(blkif->be);
	unsigned long long new_size = vbd_sz(vbd);

	pr_info("VBD Resize: Domid: %d, Device: (%d, %d)\n",
		blkif->domid, MAJOR(vbd->pdevice), MINOR(vbd->pdevice));
	pr_info("VBD Resize: new size %llu\n", new_size);
	vbd->size = new_size;
again:
	err = xenbus_transaction_start(&xbt);
	if (err) {
		pr_warn("Error starting transaction\n");
		return;
	}
	err = xenbus_printf(xbt, dev->nodename, "sectors", "%llu",
			    (unsigned long long)vbd_sz(vbd));
	if (err) {
		pr_warn("Error writing new size\n");
		goto abort;
	}
	/*
	 * Write the current state; we will use this to synchronize
	 * the front-end. If the current state is "connected" the
	 * front-end will get the new size information online.
	 */
	err = xenbus_printf(xbt, dev->nodename, "state", "%d", dev->state);
	if (err) {
		pr_warn("Error writing the state\n");
		goto abort;
	}

	err = xenbus_transaction_end(xbt, 0);
	if (err == -EAGAIN)
		goto again;
	if (err)
		pr_warn("Error ending transaction\n");
	return;
abort:
	xenbus_transaction_end(xbt, 1);
}