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
typedef  int uint64_t ;
struct rlimit {int rlim_cur; int rlim_max; } ;
typedef  scalar_t__ isc_result_t ;
typedef  scalar_t__ isc_resourcevalue_t ;
typedef  scalar_t__ isc_resource_t ;
typedef  scalar_t__ isc_boolean_t ;
typedef  int ISC_PLATFORM_RLIMITTYPE ;

/* Variables and functions */
 scalar_t__ ISC_RESOURCE_UNLIMITED ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_TF (int) ; 
 int NR_OPEN ; 
 int OPEN_MAX ; 
 int RLIM_INFINITY ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getrlimit (int,struct rlimit*) ; 
 scalar_t__ gettune (char*,int*) ; 
 scalar_t__ isc__errno2result (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_resource_openfiles ; 
 scalar_t__ resource2rlim (scalar_t__,int*) ; 
 int setrlimit (int,struct rlimit*) ; 

isc_result_t
isc_resource_setlimit(isc_resource_t resource, isc_resourcevalue_t value) {
	struct rlimit rl;
	ISC_PLATFORM_RLIMITTYPE rlim_value;
	int unixresult;
	int unixresource;
	isc_result_t result;

	result = resource2rlim(resource, &unixresource);
	if (result != ISC_R_SUCCESS)
		return (result);

	if (value == ISC_RESOURCE_UNLIMITED)
		rlim_value = RLIM_INFINITY;

	else {
		/*
		 * isc_resourcevalue_t was chosen as an unsigned 64 bit
		 * integer so that it could contain the maximum range of
		 * reasonable values.  Unfortunately, this exceeds the typical
		 * range on Unix systems.  Ensure the range of
		 * ISC_PLATFORM_RLIMITTYPE is not overflowed.
		 */
		isc_resourcevalue_t rlim_max;
		isc_boolean_t rlim_t_is_signed =
			ISC_TF(((double)(ISC_PLATFORM_RLIMITTYPE)-1) < 0);

		if (rlim_t_is_signed)
			rlim_max = ~((ISC_PLATFORM_RLIMITTYPE)1 <<
				     (sizeof(ISC_PLATFORM_RLIMITTYPE) * 8 - 1));
		else
			rlim_max = (ISC_PLATFORM_RLIMITTYPE)-1;

		if (value > rlim_max)
			value = rlim_max;

		rlim_value = value;
	}

	rl.rlim_cur = rl.rlim_max = rlim_value;
	unixresult = setrlimit(unixresource, &rl);

	if (unixresult == 0)
		return (ISC_R_SUCCESS);

#if defined(OPEN_MAX) && defined(__APPLE__)
	/*
	 * The Darwin kernel doesn't accept RLIM_INFINITY for rlim_cur; the
	 * maximum possible value is OPEN_MAX.  BIND8 used to use
	 * sysconf(_SC_OPEN_MAX) for such a case, but this value is much
	 * smaller than OPEN_MAX and is not really effective.
	 */
	if (resource == isc_resource_openfiles && rlim_value == RLIM_INFINITY) {
		rl.rlim_cur = OPEN_MAX;
		unixresult = setrlimit(unixresource, &rl);
		if (unixresult == 0)
			return (ISC_R_SUCCESS);
	}
#elif defined(__linux__)
#ifndef NR_OPEN
#define NR_OPEN (1024*1024)
#endif

	/*
	 * Some Linux kernels don't accept RLIM_INFINIT; the maximum
	 * possible value is the NR_OPEN defined in linux/fs.h.
	 */
	if (resource == isc_resource_openfiles && rlim_value == RLIM_INFINITY) {
		rl.rlim_cur = rl.rlim_max = NR_OPEN;
		unixresult = setrlimit(unixresource, &rl);
		if (unixresult == 0)
			return (ISC_R_SUCCESS);
	}
#elif defined(__hpux) && defined(HAVE_SYS_DYNTUNE_H)
	if (resource == isc_resource_openfiles && rlim_value == RLIM_INFINITY) {
		uint64_t maxfiles;
		if (gettune("maxfiles_lim", &maxfiles) == 0) {
			rl.rlim_cur = rl.rlim_max = maxfiles;
			unixresult = setrlimit(unixresource, &rl);
			if (unixresult == 0)
				return (ISC_R_SUCCESS);
		}
	}
#endif
	if (resource == isc_resource_openfiles && rlim_value == RLIM_INFINITY) {
		if (getrlimit(unixresource, &rl) == 0) {
			rl.rlim_cur = rl.rlim_max;
			unixresult = setrlimit(unixresource, &rl);
			if (unixresult == 0)
				return (ISC_R_SUCCESS);
		}
	}
	return (isc__errno2result(errno));
}