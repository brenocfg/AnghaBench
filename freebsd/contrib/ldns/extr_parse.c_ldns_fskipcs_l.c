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
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

void
ldns_fskipcs_l(FILE *fp, const char *s, int *line_nr)
{
        bool found;
        int c;
        const char *d;

	while ((c = fgetc(fp)) != EOF) {
		if (line_nr && c == '\n') {
			*line_nr = *line_nr + 1;
		}
                found = false;
                for (d = s; *d; d++) {
                        if (*d == c) {
                                found = true;
                        }
                }
		if (!found) {
			/* with getc, we've read too far */
			ungetc(c, fp);
			return;
		}
	}
}