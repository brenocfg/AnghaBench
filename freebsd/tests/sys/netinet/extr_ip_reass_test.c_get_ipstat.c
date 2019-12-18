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
struct ipstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct ipstat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctlbyname (char*,struct ipstat*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_ipstat(struct ipstat *stat)
{
	size_t len;
	int error;

	memset(stat, 0, sizeof(*stat));
	len = sizeof(*stat);
	error = sysctlbyname("net.inet.ip.stats", stat, &len, NULL, 0);
	ATF_REQUIRE_MSG(error == 0, "sysctl(net.inet.ip.stats) failed: %s",
	    strerror(errno));
	ATF_REQUIRE(len == sizeof(*stat));
}