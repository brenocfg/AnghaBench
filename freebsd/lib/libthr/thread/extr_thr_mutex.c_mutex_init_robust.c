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
struct umtx_robust_lists_params {uintptr_t robust_list_offset; uintptr_t robust_priv_list_offset; uintptr_t robust_inact_offset; } ;
struct pthread {int robust_inited; int /*<<< orphan*/  inact_mtx; int /*<<< orphan*/  priv_robust_list; int /*<<< orphan*/  robust_list; } ;
typedef  int /*<<< orphan*/  rb ;

/* Variables and functions */
 int /*<<< orphan*/  UMTX_OP_ROBUST_LISTS ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _umtx_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct umtx_robust_lists_params*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mutex_init_robust(struct pthread *curthread)
{
	struct umtx_robust_lists_params rb;

	if (curthread == NULL)
		curthread = _get_curthread();
	if (curthread->robust_inited)
		return;
	rb.robust_list_offset = (uintptr_t)&curthread->robust_list;
	rb.robust_priv_list_offset = (uintptr_t)&curthread->priv_robust_list;
	rb.robust_inact_offset = (uintptr_t)&curthread->inact_mtx;
	_umtx_op(NULL, UMTX_OP_ROBUST_LISTS, sizeof(rb), &rb, NULL);
	curthread->robust_inited = 1;
}