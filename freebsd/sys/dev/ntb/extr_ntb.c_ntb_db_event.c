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
typedef  int /*<<< orphan*/  uint32_t ;
struct rm_priotracker {int dummy; } ;
struct ntb_child {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx; TYPE_1__* ctx_ops; struct ntb_child* next; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* db_event ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ntb_child** device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ntb_db_event(device_t dev, uint32_t vec)
{
	struct ntb_child **cpp = device_get_softc(dev);
	struct ntb_child *nc;
	struct rm_priotracker ctx_tracker;

	for (nc = *cpp; nc != NULL; nc = nc->next) {
		rm_rlock(&nc->ctx_lock, &ctx_tracker);
		if (nc->ctx_ops != NULL && nc->ctx_ops->db_event != NULL)
			nc->ctx_ops->db_event(nc->ctx, vec);
		rm_runlock(&nc->ctx_lock, &ctx_tracker);
	}
}