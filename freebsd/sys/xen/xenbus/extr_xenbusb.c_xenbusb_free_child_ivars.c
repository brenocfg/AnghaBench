#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct xenbus_device_ivars* node; } ;
struct xenbus_device_ivars {scalar_t__ xd_otherend_path_len; struct xenbus_device_ivars* xd_otherend_path; struct xenbus_device_ivars* xd_type; scalar_t__ xd_node_len; struct xenbus_device_ivars* xd_node; TYPE_1__ xd_local_watch; TYPE_1__ xd_otherend_watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENBUS ; 
 int /*<<< orphan*/  free (struct xenbus_device_ivars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_unregister_watch (TYPE_1__*) ; 

__attribute__((used)) static void
xenbusb_free_child_ivars(struct xenbus_device_ivars *ivars)
{
	if (ivars->xd_otherend_watch.node != NULL) {
		xs_unregister_watch(&ivars->xd_otherend_watch);
		free(ivars->xd_otherend_watch.node, M_XENBUS);
		ivars->xd_otherend_watch.node = NULL;
	}

	if (ivars->xd_local_watch.node != NULL) {
		xs_unregister_watch(&ivars->xd_local_watch);
		ivars->xd_local_watch.node = NULL;
	}

	if (ivars->xd_node != NULL) {
		free(ivars->xd_node, M_XENBUS);
		ivars->xd_node = NULL;
	}
	ivars->xd_node_len = 0;

	if (ivars->xd_type != NULL) {
		free(ivars->xd_type, M_XENBUS);
		ivars->xd_type = NULL;
	}

	if (ivars->xd_otherend_path != NULL) {
		free(ivars->xd_otherend_path, M_XENBUS);
		ivars->xd_otherend_path = NULL;
	}
	ivars->xd_otherend_path_len = 0;

	free(ivars, M_XENBUS);
}