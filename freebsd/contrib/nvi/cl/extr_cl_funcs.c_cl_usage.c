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
 char* USAGE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
cl_usage(void)
{
#define	USAGE "\
usage: ex [-eFRrSsv] [-c command] [-t tag] [-w size] [file ...]\n\
usage: vi [-eFlRrSv] [-c command] [-t tag] [-w size] [file ...]\n"
	(void)fprintf(stderr, "%s", USAGE);
#undef	USAGE
}