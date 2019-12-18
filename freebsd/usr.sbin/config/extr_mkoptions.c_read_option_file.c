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
typedef  int /*<<< orphan*/  genopt ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_option (char const*,char*,char*) ; 
 char* lower (char*) ; 
 char* ns (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_option (char*,char*,int) ; 

__attribute__((used)) static int
read_option_file(const char *fname, int flags)
{
	FILE *fp;
	char *wd, *this, *val;
	char genopt[MAXPATHLEN];

	fp = fopen(fname, "r");
	if (fp == NULL)
		return (0);
	while ((wd = get_word(fp)) != (char *)EOF) {
		if (wd == NULL)
			continue;
		if (wd[0] == '#') {
			while (((wd = get_word(fp)) != (char *)EOF) && wd)
				continue;
			continue;
		}
		this = ns(wd);
		val = get_word(fp);
		if (val == (char *)EOF)
			return (1);
		if (val == NULL) {
			if (flags) {
				fprintf(stderr, "%s: compat file requires two"
				    " words per line at %s\n", fname, this);
				exit(1);
			}
			char *s = ns(this);
			(void)snprintf(genopt, sizeof(genopt), "opt_%s.h",
			    lower(s));
			val = genopt;
			free(s);
		}
		val = ns(val);
		if (flags == 0)
			insert_option(fname, this, val);
		else
			update_option(this, val, flags);
	}
	(void)fclose(fp);
	return (1);
}