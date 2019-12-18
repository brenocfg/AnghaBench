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
typedef  int /*<<< orphan*/  acctstr ;

/* Variables and functions */
 int /*<<< orphan*/  UI_UTIL_read_pw_string (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
account(int argc, char **argv)
{
	char acctstr[50];

	if (argc > 1) {
		++argv;
		--argc;
		strlcpy (acctstr, *argv, sizeof(acctstr));
		while (argc > 1) {
			--argc;
			++argv;
			strlcat(acctstr, *argv, sizeof(acctstr));
		}
	}
	else {
	    UI_UTIL_read_pw_string(acctstr, sizeof(acctstr), "Account:", 0);
	}
	command("ACCT %s", acctstr);
}