#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key_specs {size_t f2; size_t f1; size_t c2; size_t c1; int pos2b; int pos1b; int /*<<< orphan*/  sm; } ;
typedef  size_t regoff_t ;
struct TYPE_3__ {scalar_t__ rm_eo; scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  check_mutually_exclusive_flags (char const,int*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getstr (int) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sort_modifier (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  sort_free (char*) ; 
 char* sort_malloc (size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_pos(const char *s, struct key_specs *ks, bool *mef_flags, bool second)
{
	regmatch_t pmatch[4];
	regex_t re;
	char *c, *f;
	const char *sregexp = "^([0-9]+)(\\.[0-9]+)?([bdfirMngRhV]+)?$";
	size_t len, nmatch;
	int ret;

	ret = -1;
	nmatch = 4;
	c = f = NULL;

	if (regcomp(&re, sregexp, REG_EXTENDED) != 0)
		return (-1);

	if (regexec(&re, s, nmatch, pmatch, 0) != 0)
		goto end;

	if (pmatch[0].rm_eo <= pmatch[0].rm_so)
		goto end;

	if (pmatch[1].rm_eo <= pmatch[1].rm_so)
		goto end;

	len = pmatch[1].rm_eo - pmatch[1].rm_so;
	f = sort_malloc((len + 1) * sizeof(char));

	strncpy(f, s + pmatch[1].rm_so, len);
	f[len] = '\0';

	if (second) {
		errno = 0;
		ks->f2 = (size_t) strtoul(f, NULL, 10);
		if (errno != 0)
			err(2, "-k");
		if (ks->f2 == 0) {
			warn("%s",getstr(5));
			goto end;
		}
	} else {
		errno = 0;
		ks->f1 = (size_t) strtoul(f, NULL, 10);
		if (errno != 0)
			err(2, "-k");
		if (ks->f1 == 0) {
			warn("%s",getstr(5));
			goto end;
		}
	}

	if (pmatch[2].rm_eo > pmatch[2].rm_so) {
		len = pmatch[2].rm_eo - pmatch[2].rm_so - 1;
		c = sort_malloc((len + 1) * sizeof(char));

		strncpy(c, s + pmatch[2].rm_so + 1, len);
		c[len] = '\0';

		if (second) {
			errno = 0;
			ks->c2 = (size_t) strtoul(c, NULL, 10);
			if (errno != 0)
				err(2, "-k");
		} else {
			errno = 0;
			ks->c1 = (size_t) strtoul(c, NULL, 10);
			if (errno != 0)
				err(2, "-k");
			if (ks->c1 == 0) {
				warn("%s",getstr(6));
				goto end;
			}
		}
	} else {
		if (second)
			ks->c2 = 0;
		else
			ks->c1 = 1;
	}

	if (pmatch[3].rm_eo > pmatch[3].rm_so) {
		regoff_t i = 0;

		for (i = pmatch[3].rm_so; i < pmatch[3].rm_eo; i++) {
			check_mutually_exclusive_flags(s[i], mef_flags);
			if (s[i] == 'b') {
				if (second)
					ks->pos2b = true;
				else
					ks->pos1b = true;
			} else if (!set_sort_modifier(&(ks->sm), s[i]))
				goto end;
		}
	}

	ret = 0;

end:

	if (c)
		sort_free(c);
	if (f)
		sort_free(f);
	regfree(&re);

	return (ret);
}