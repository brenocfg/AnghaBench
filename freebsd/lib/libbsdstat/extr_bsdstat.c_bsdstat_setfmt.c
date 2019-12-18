#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bsdstat {int nstats; char* name; char* fmts; TYPE_1__* stats; } ;
typedef  int /*<<< orphan*/  fmt ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char FMTS_IS_STAT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
bsdstat_setfmt(struct bsdstat *sf, const char *fmt0)
{
#define	N(a)	(sizeof(a)/sizeof(a[0]))
	char fmt[4096];
	char *fp, *tok;
	int i, j;

	j = 0;
	strlcpy(fmt, fmt0, sizeof(fmt));
	for (fp = fmt; (tok = strsep(&fp, ", ")) != NULL;) {
		for (i = 0; i < sf->nstats; i++)
			if (strcasecmp(tok, sf->stats[i].name) == 0)
				break;
		if (i >= sf->nstats) {
			fprintf(stderr, "%s: unknown statistic name \"%s\" "
				"skipped\n", sf->name, tok);
			continue;
		}
		if (j+4 > (int) sizeof(sf->fmts)) {
			fprintf(stderr, "%s: not enough room for all stats; "
				"stopped at %s\n", sf->name, tok);
			break;
		}
		if (j != 0)
			sf->fmts[j++] = ' ';
		sf->fmts[j++] = FMTS_IS_STAT;
		sf->fmts[j++] = i & 0xff;
		sf->fmts[j++] = (i >> 8) & 0xff;
	}
	sf->fmts[j] = '\0';
#undef N
}