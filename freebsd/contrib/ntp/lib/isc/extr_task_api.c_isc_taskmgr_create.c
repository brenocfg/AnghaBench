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
typedef  int /*<<< orphan*/  isc_taskmgr_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createlock ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskmgr_createfunc (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ **) ; 

isc_result_t
isc_taskmgr_create(isc_mem_t *mctx, unsigned int workers,
		   unsigned int default_quantum, isc_taskmgr_t **managerp)
{
	isc_result_t result;

	LOCK(&createlock);

	REQUIRE(taskmgr_createfunc != NULL);
	result = (*taskmgr_createfunc)(mctx, workers, default_quantum,
				       managerp);

	UNLOCK(&createlock);

	return (result);
}