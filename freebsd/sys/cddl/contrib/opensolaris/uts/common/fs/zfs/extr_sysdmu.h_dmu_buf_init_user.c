#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** dbu_clear_on_evict_dbufp; int /*<<< orphan*/ * dbu_evict_func_async; int /*<<< orphan*/ * dbu_evict_func_sync; } ;
typedef  TYPE_1__ dmu_buf_user_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_evict_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMPLY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void
dmu_buf_init_user(dmu_buf_user_t *dbu, dmu_buf_evict_func_t *evict_func_sync,
    dmu_buf_evict_func_t *evict_func_async, dmu_buf_t **clear_on_evict_dbufp)
{
	ASSERT(dbu->dbu_evict_func_sync == NULL);
	ASSERT(dbu->dbu_evict_func_async == NULL);

	/* must have at least one evict func */
	IMPLY(evict_func_sync == NULL, evict_func_async != NULL);
	dbu->dbu_evict_func_sync = evict_func_sync;
	dbu->dbu_evict_func_async = evict_func_async;
#ifdef ZFS_DEBUG
	dbu->dbu_clear_on_evict_dbufp = clear_on_evict_dbufp;
#endif
}