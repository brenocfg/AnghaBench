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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
Usage(void)
{
	fprintf(stderr,
		"Usage: fiforead [options] fifofile\n"
		"\t-b <start time integer>\n"
		"\t-B <start time>\n"
		"\t-e <end time integer>\n"
		"\t-E <end time>\n"
		"\t-o <output file>\n"
		"\t-R <regexp> # match regexp\n"
		"\t-t # format timestamps as %%Y%%m%%d%%H%%M%%S\n"
		"\t-T <timestamp format>\n"
	);
	exit (EX_USAGE);
}