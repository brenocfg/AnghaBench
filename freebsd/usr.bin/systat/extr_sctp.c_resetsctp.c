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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  initstat ; 
 int /*<<< orphan*/  oldstat ; 
 scalar_t__ sysctlbyname (char const*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
resetsctp(void)
{
	size_t len;
	const char *name = "net.inet.sctp.stats";

	len = sizeof initstat;
	if (sysctlbyname(name, &initstat, &len, NULL, 0) < 0) {
		error("sysctl getting sctpstat failed");
	}
	oldstat = initstat;
}