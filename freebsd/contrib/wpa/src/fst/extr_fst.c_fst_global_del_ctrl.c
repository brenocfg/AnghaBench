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
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) () ;} ;
struct fst_ctrl_handle {TYPE_1__ ctrl; int /*<<< orphan*/  global_ctrls_lentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct fst_ctrl_handle*) ; 
 int /*<<< orphan*/  stub1 () ; 

void fst_global_del_ctrl(struct fst_ctrl_handle *h)
{
	dl_list_del(&h->global_ctrls_lentry);
	if (h->ctrl.deinit)
		h->ctrl.deinit();
	os_free(h);
}