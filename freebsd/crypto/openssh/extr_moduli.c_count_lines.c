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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int QLINESIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long
count_lines(FILE *f)
{
	unsigned long count = 0;
	char lp[QLINESIZE + 1];

	if (fseek(f, 0, SEEK_SET) != 0) {
		debug("input file is not seekable");
		return ULONG_MAX;
	}
	while (fgets(lp, QLINESIZE + 1, f) != NULL)
		count++;
	rewind(f);
	debug("input file has %lu lines", count);
	return count;
}