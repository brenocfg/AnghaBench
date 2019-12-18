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
 int CheckIpfwRulenum (unsigned int) ; 
 int /*<<< orphan*/  LibAliasSetFWBase (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LibAliasSetMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_ALIAS_PUNCH_FW ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  mla ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void
SetupPunchFW(const char *strValue)
{
	unsigned int base, num;

	if (sscanf(strValue, "%u:%u", &base, &num) != 2)
		errx(1, "punch_fw: basenumber:count parameter required");

	if (CheckIpfwRulenum(base + num - 1) == -1)
		errx(1, "punch_fw: basenumber:count parameter should fit "
			"the maximum allowed rule numbers");

	LibAliasSetFWBase(mla, base, num);
	(void)LibAliasSetMode(mla, PKT_ALIAS_PUNCH_FW, PKT_ALIAS_PUNCH_FW);
}