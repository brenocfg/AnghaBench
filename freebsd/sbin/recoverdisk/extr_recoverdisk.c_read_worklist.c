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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  new_lump (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  rworklist ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static off_t
read_worklist(off_t t)
{
	off_t s, l, d;
	int state, lines;
	FILE *file;

	(void)fprintf(stderr, "Reading worklist ...");
	fflush(stderr);
	file = fopen(rworklist, "r");
	if (file == NULL)
		err(1, "Error opening file %s", rworklist);

	lines = 0;
	d = t;
	for (;;) {
		++lines;
		if (3 != fscanf(file, "%jd %jd %d\n", &s, &l, &state)) {
			if (!feof(file))
				err(1, "Error parsing file %s at line %d",
				    rworklist, lines);
			else
				break;
		}
		new_lump(s, l, state);
		d -= l;
	}
	fclose(file);
	(void)fprintf(stderr, " done.\n");
	/*
	 * Return the number of bytes already read
	 * (at least not in worklist).
	 */
	return (d);
}