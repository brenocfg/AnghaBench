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

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_FAILURE ; 
 int /*<<< orphan*/  ISC_R_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  UNUSED (int) ; 

isc_result_t
isc_backtrace_gettrace(void **addrs, int maxaddrs, int *nframes) {
	/* Argument validation: see above. */
	if (addrs == NULL || nframes == NULL)
		return (ISC_R_FAILURE);

	UNUSED(maxaddrs);

	return (ISC_R_NOTIMPLEMENTED);
}