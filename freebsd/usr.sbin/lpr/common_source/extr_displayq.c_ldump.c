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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

void
ldump(const char *nfile, const char *datafile, int copies)
{
	struct stat lbuf;

	putchar('\t');
	if (copies > 1)
		printf("%-2d copies of %-19s", copies, nfile);
	else
		printf("%-32s", nfile);
	if (*datafile && !stat(datafile, &lbuf))
		printf(" %qd bytes", (long long) lbuf.st_size);
	else
		printf(" ??? bytes");
	putchar('\n');
}