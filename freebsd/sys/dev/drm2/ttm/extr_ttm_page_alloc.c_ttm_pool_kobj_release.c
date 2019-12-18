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
struct ttm_pool_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_POOLMGR ; 
 int /*<<< orphan*/  free (struct ttm_pool_manager*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_pool_kobj_release(struct ttm_pool_manager *m)
{

	free(m, M_TTM_POOLMGR);
}