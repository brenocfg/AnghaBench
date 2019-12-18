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

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int sysctlbyname (char const*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
get_sysctl(const char *name, void *buf, const size_t len)
{
	size_t len2 = len;
	printf("Querying sysctl variable: %s\n", name);
	int ret = sysctlbyname(name, buf, &len2, NULL, 0);
	if (ret == -1 && errno != ENOENT) {
		fprintf(stderr, "sysctlbyname(2) failed: %s\n",
		    strerror(errno));
		atf_tc_fail("Failed to query %s", name);
	}
	return ret != -1;
}