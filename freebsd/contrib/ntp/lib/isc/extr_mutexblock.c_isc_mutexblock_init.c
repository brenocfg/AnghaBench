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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 

isc_result_t
isc_mutexblock_init(isc_mutex_t *block, unsigned int count) {
	isc_result_t result;
	unsigned int i;

	for (i = 0; i < count; i++) {
		result = isc_mutex_init(&block[i]);
		if (result != ISC_R_SUCCESS) {
			while (i > 0U) {
				i--;
				DESTROYLOCK(&block[i]);
			}
			return (result);
		}
	}

	return (ISC_R_SUCCESS);
}