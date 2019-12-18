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
typedef  int u_short ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  icmp6codes ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

void
fill_unreach6_code(u_short *codep, char *str)
{
	int val;
	char *s;

	val = strtoul(str, &s, 0);
	if (s == str || *s != '\0' || val >= 0x100)
		val = match_token(icmp6codes, str);
	if (val < 0)
		errx(EX_DATAERR, "unknown ICMPv6 unreachable code ``%s''", str);
	*codep = val;
	return;
}