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
struct in_multi_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_CONCAT (int /*<<< orphan*/ *,struct in_multi_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIST_EMPTY (struct in_multi_head*) ; 
 int /*<<< orphan*/  free_gtask ; 
 int /*<<< orphan*/  in_multi ; 
 int /*<<< orphan*/  in_multi_free_mtx ; 
 int /*<<< orphan*/  inm_free_list ; 
 int /*<<< orphan*/  inm_nrele ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
inm_release_list_deferred(struct in_multi_head *inmh)
{

	if (SLIST_EMPTY(inmh))
		return;
	mtx_lock(&in_multi_free_mtx);
	SLIST_CONCAT(&inm_free_list, inmh, in_multi, inm_nrele);
	mtx_unlock(&in_multi_free_mtx);
	GROUPTASK_ENQUEUE(&free_gtask);
}