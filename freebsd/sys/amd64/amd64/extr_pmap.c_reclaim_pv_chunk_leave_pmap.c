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
typedef  int /*<<< orphan*/ * pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_delayed_invl_finish () ; 
 int /*<<< orphan*/  pmap_invalidate_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reclaim_pv_chunk_leave_pmap(pmap_t pmap, pmap_t locked_pmap, bool start_di)
{

	if (pmap == NULL)
		return;
	pmap_invalidate_all(pmap);
	if (pmap != locked_pmap)
		PMAP_UNLOCK(pmap);
	if (start_di)
		pmap_delayed_invl_finish();
}