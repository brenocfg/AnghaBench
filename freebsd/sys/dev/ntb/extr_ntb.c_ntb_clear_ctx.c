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
struct ntb_child {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/ * ctx_ops; int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_wunlock (int /*<<< orphan*/ *) ; 

void
ntb_clear_ctx(device_t ntb)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	rm_wlock(&nc->ctx_lock);
	nc->ctx = NULL;
	nc->ctx_ops = NULL;
	rm_wunlock(&nc->ctx_lock);
}