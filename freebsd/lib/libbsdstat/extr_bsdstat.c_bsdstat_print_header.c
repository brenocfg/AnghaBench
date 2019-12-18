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
struct fmt {char* width; int /*<<< orphan*/  label; } ;
struct bsdstat {unsigned char* fmts; struct fmt* stats; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char const FMTS_IS_STAT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (unsigned char const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bsdstat_print_header(struct bsdstat *sf, FILE *fd)
{
	const unsigned char *cp;
	int i;
	const struct fmt *f;

	for (cp = sf->fmts; *cp != '\0'; cp++) {
		if (*cp == FMTS_IS_STAT) {
			i = *(++cp);
			i |= ((int) *(++cp)) << 8;
			f = &sf->stats[i];
			fprintf(fd, "%*s", f->width, f->label);
		} else
			putc(*cp, fd);
	}
	putc('\n', fd);
}