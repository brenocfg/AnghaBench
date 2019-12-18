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
typedef  int /*<<< orphan*/  default_rule ;

/* Variables and functions */
 int sysctlbyname (char*,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
CheckIpfwRulenum(unsigned int rnum)
{
	unsigned int default_rule;
	size_t len = sizeof(default_rule);

	if (sysctlbyname("net.inet.ip.fw.default_rule", &default_rule, &len,
		NULL, 0) == -1) {
		warn("Failed to get the default ipfw rule number, using "
		     "default historical value 65535.  The reason was");
		default_rule = 65535;
	}
	if (rnum >= default_rule) {
		return -1;
	}

	return 0;
}