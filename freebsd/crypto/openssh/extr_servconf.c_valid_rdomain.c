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
struct rt_tableinfo {int dummy; } ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int CTL_NET ; 
 int NET_RT_TABLE ; 
 int PF_ROUTE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 long long strtonum (char const*,int /*<<< orphan*/ ,int,char const**) ; 
 int sys_valid_rdomain (char const*) ; 
 int sysctl (int*,int,struct rt_tableinfo*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
valid_rdomain(const char *name)
{
#if defined(HAVE_SYS_VALID_RDOMAIN)
	return sys_valid_rdomain(name);
#elif defined(__OpenBSD__)
	const char *errstr;
	long long num;
	struct rt_tableinfo info;
	int mib[6];
	size_t miblen = sizeof(mib);

	if (name == NULL)
		return 1;

	num = strtonum(name, 0, 255, &errstr);
	if (errstr != NULL)
		return 0;

	/* Check whether the table actually exists */
	memset(mib, 0, sizeof(mib));
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[4] = NET_RT_TABLE;
	mib[5] = (int)num;
	if (sysctl(mib, 6, &info, &miblen, NULL, 0) == -1)
		return 0;

	return 1;
#else /* defined(__OpenBSD__) */
	error("Routing domains are not supported on this platform");
	return 0;
#endif
}