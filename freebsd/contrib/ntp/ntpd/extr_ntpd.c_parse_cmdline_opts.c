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
 int ntpOptionProcess (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  ntpdOptions ; 

void
parse_cmdline_opts(
	int *	pargc,
	char ***pargv
	)
{
	static int	parsed;
	static int	optct;

	if (!parsed)
		optct = ntpOptionProcess(&ntpdOptions, *pargc, *pargv);

	parsed = 1;
	
	*pargc -= optct;
	*pargv += optct;
}