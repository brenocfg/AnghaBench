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
struct fst_ctrl {scalar_t__ (* init ) () ;} ;
struct fst_ctrl_handle {int /*<<< orphan*/  global_ctrls_lentry; struct fst_ctrl ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_global_ctrls_list ; 
 int /*<<< orphan*/  os_free (struct fst_ctrl_handle*) ; 
 struct fst_ctrl_handle* os_zalloc (int) ; 
 scalar_t__ stub1 () ; 

struct fst_ctrl_handle * fst_global_add_ctrl(const struct fst_ctrl *ctrl)
{
	struct fst_ctrl_handle *h;

	if (!ctrl)
		return NULL;

	h = os_zalloc(sizeof(*h));
	if (!h)
		return NULL;

	if (ctrl->init && ctrl->init()) {
		os_free(h);
		return NULL;
	}

	h->ctrl = *ctrl;
	dl_list_add_tail(&fst_global_ctrls_list, &h->global_ctrls_lentry);

	return h;
}