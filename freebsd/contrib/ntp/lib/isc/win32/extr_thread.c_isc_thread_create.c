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
typedef  int /*<<< orphan*/  isc_threadfunc_t ;
typedef  int /*<<< orphan*/  isc_threadarg_t ;
typedef  int /*<<< orphan*/ * isc_thread_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

isc_result_t
isc_thread_create(isc_threadfunc_t start, isc_threadarg_t arg,
		  isc_thread_t *threadp)
{
	isc_thread_t thread;
	unsigned int id;

	thread = (isc_thread_t)_beginthreadex(NULL, 0, start, arg, 0, &id);
	if (thread == NULL) {
		/* XXX */
		return (ISC_R_UNEXPECTED);
	}

	*threadp = thread;

	return (ISC_R_SUCCESS);
}