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
typedef  int /*<<< orphan*/  ncpu ;

/* Variables and functions */
 int DEFNFSDCNT ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static int
get_tuned_nfsdcount(void)
{
	int ncpu, error, tuned_nfsdcnt;
	size_t ncpu_size;

	ncpu_size = sizeof(ncpu);
	error = sysctlbyname("hw.ncpu", &ncpu, &ncpu_size, NULL, 0);
	if (error) {
		warnx("sysctlbyname(hw.ncpu) failed defaulting to %d nfs servers",
		    DEFNFSDCNT);
		tuned_nfsdcnt = DEFNFSDCNT;
	} else {
		tuned_nfsdcnt = ncpu * 8;
	}
	return tuned_nfsdcnt;
}