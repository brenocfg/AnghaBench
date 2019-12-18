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
struct label_specs {int /*<<< orphan*/  head; } ;
struct label_spec {size_t nentries; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct label_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_spec_line (char const*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int chomp_line (char**,size_t*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  link ; 
 struct label_spec* malloc (int) ; 
 int /*<<< orphan*/  qflag ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,char const*,long) ; 

void
add_specs(struct label_specs *specs, const char *file, int is_sebsd)
{
	struct label_spec *spec;
	FILE *fp;
	char *line;
	size_t nlines = 0, linesize;
	int freeline;

	spec = malloc(sizeof(*spec));
	if (spec == NULL)
		err(1, "malloc");
	fp = fopen(file, "r");
	if (fp == NULL)
		err(1, "opening %s", file);
	while ((line = fgetln(fp, &linesize)) != NULL) {
		freeline = chomp_line(&line, &linesize);
		if (linesize > 0) /* only allocate space for non-comments */
			nlines++;
		if (freeline)
			free(line);
	}
	if (ferror(fp))
		err(1, "fgetln on %s", file);
	rewind(fp);
	spec->entries = calloc(nlines, sizeof(*spec->entries));
	if (spec->entries == NULL)
		err(1, "malloc");
	spec->nentries = nlines;
	while (nlines > 0) {
		line = fgetln(fp, &linesize);
		if (line == NULL) {
			if (feof(fp))
				errx(1, "%s ended prematurely", file);
			else
				err(1, "failure reading %s", file);
		}
		freeline = chomp_line(&line, &linesize);
		if (linesize == 0) {
			if (freeline)
				free(line);
			continue;
		}
		add_spec_line(file, is_sebsd, &spec->entries[--nlines], line);
		if (freeline)
			free(line);
	}
	fclose(fp);
	if (!qflag)
		warnx("%s: read %lu specifications", file,
		    (long)spec->nentries);
	STAILQ_INSERT_TAIL(&specs->head, spec, link);
}