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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_MEMFLAG_DEFAULT ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createlock ; 
 int /*<<< orphan*/  mem_createfunc (size_t,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (size_t,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

isc_result_t
isc_mem_create(size_t init_max_size, size_t target_size, isc_mem_t **mctxp) {
	isc_result_t result;

	LOCK(&createlock);

	REQUIRE(mem_createfunc != NULL);
	result = (*mem_createfunc)(init_max_size, target_size, mctxp,
				   ISC_MEMFLAG_DEFAULT);

	UNLOCK(&createlock);

	return (result);
}