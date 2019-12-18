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
 int /*<<< orphan*/  dump (char const*,char const*,int) ; 
 int /*<<< orphan*/  ldump (char const*,char const*,int) ; 
 scalar_t__ lflag ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
show(const char *nfile, const char *datafile, int copies)
{
	if (strcmp(nfile, " ") == 0)
		nfile = "(standard input)";
	if (lflag)
		ldump(nfile, datafile, copies);
	else
		dump(nfile, datafile, copies);
}