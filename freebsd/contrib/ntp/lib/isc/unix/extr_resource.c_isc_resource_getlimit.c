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
struct rlimit {int /*<<< orphan*/  rlim_max; } ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_resourcevalue_t ;
typedef  int /*<<< orphan*/  isc_resource_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int getrlimit (int,struct rlimit*) ; 
 scalar_t__ resource2rlim (int /*<<< orphan*/ ,int*) ; 

isc_result_t
isc_resource_getlimit(isc_resource_t resource, isc_resourcevalue_t *value) {
	int unixresult;
	int unixresource;
	struct rlimit rl;
	isc_result_t result;

	result = resource2rlim(resource, &unixresource);
	if (result == ISC_R_SUCCESS) {
		unixresult = getrlimit(unixresource, &rl);
		INSIST(unixresult == 0);
		*value = rl.rlim_max;
	}

	return (result);
}