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
typedef  scalar_t__ uint16_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NUM_PER_LINE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
do_eeprom_dump(const char *dumpfile, uint16_t *eebuf, int eelen)
{
	FILE *fp;
	int i;

	fp = fopen(dumpfile, "w");
	if (!fp) {
		err(1, "fopen");
	}

	/* eelen is in bytes; eebuf is in 2 byte words */
	for (i = 0; i < eelen / 2; i++) {
		if (i % NUM_PER_LINE == 0)
			fprintf(fp, "%.4x: ", i);
		fprintf(fp, "%.4x%s", (int32_t)(eebuf[i]), i % NUM_PER_LINE == (NUM_PER_LINE - 1) ? "\n" : " ");
	}
	fprintf(fp, "\n");
	fclose(fp);
}