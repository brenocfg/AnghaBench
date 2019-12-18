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
 int /*<<< orphan*/  _errbuf ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ inetdflag ; 
 scalar_t__ logflag ; 
 scalar_t__ pmflag ; 

__attribute__((used)) static void
print_err_message(const char *space)
{
	if (logflag)
		f_print(fout, "%ssyslog(LOG_ERR, \"%s\");\n", space, _errbuf);
	else if (inetdflag || pmflag)
		f_print(fout, "%s_msgout(\"%s\");\n", space, _errbuf);
	else
		f_print(fout, "%sfprintf(stderr, \"%s\");\n", space, _errbuf);
}