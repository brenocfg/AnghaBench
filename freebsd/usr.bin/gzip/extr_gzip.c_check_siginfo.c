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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned long long,...) ; 
 char* infile ; 
 double infile_current ; 
 int infile_total ; 
 scalar_t__ print_info ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_siginfo(void)
{
	if (print_info == 0)
		return;
	if (infile) {
		if (infile_total) {
			int pcent = (int)((100.0 * infile_current) / infile_total);

			fprintf(stderr, "%s: done %llu/%llu bytes %d%%\n",
				infile, (unsigned long long)infile_current,
				(unsigned long long)infile_total, pcent);
		} else
			fprintf(stderr, "%s: done %llu bytes\n",
				infile, (unsigned long long)infile_current);
	}
	print_info = 0;
}