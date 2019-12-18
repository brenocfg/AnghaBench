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
struct md_utrap {int /*<<< orphan*/  ut_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_pool_lock (int /*<<< orphan*/ ,struct md_utrap*) ; 
 int /*<<< orphan*/  mtx_pool_unlock (int /*<<< orphan*/ ,struct md_utrap*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 

struct md_utrap *
utrap_hold(struct md_utrap *ut)
{

	if (ut == NULL)
		return (NULL);
	mtx_pool_lock(mtxpool_sleep, ut);
	ut->ut_refcnt++;
	mtx_pool_unlock(mtxpool_sleep, ut);
	return (ut);
}