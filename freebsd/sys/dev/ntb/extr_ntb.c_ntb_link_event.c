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
struct rm_priotracker {int dummy; } ;
struct ntb_child {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx; TYPE_1__* ctx_ops; struct ntb_child* next; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_event ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ NTB_LINK_IS_UP (int /*<<< orphan*/ ,int*,int*) ; 
 struct ntb_child** device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ntb_link_event(device_t dev)
{
	struct ntb_child **cpp = device_get_softc(dev);
	struct ntb_child *nc;
	struct rm_priotracker ctx_tracker;
	enum ntb_speed speed;
	enum ntb_width width;

	if (NTB_LINK_IS_UP(dev, &speed, &width)) {
		device_printf(dev, "Link is up (PCIe %d.x / x%d)\n",
		    (int)speed, (int)width);
	} else {
		device_printf(dev, "Link is down\n");
	}
	for (nc = *cpp; nc != NULL; nc = nc->next) {
		rm_rlock(&nc->ctx_lock, &ctx_tracker);
		if (nc->ctx_ops != NULL && nc->ctx_ops->link_event != NULL)
			nc->ctx_ops->link_event(nc->ctx);
		rm_runlock(&nc->ctx_lock, &ctx_tracker);
	}
}