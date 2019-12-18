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
struct netgrp {char** ng_str; struct netgrp* ng_next; } ;
struct linelist {int l_parsed; char* l_line; int /*<<< orphan*/  l_groupname; struct linelist* l_next; } ;
struct TYPE_2__ {struct netgrp* gr; } ;

/* Variables and functions */
 size_t NG_DOM ; 
 size_t NG_HOST ; 
 size_t NG_USER ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 TYPE_1__ grouphead ; 
 struct linelist* linehead ; 
 scalar_t__ malloc (int) ; 
 struct linelist* read_for_group (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static int
parse_netgrp(char *group)
{
	char *spos, *epos;
	int len, strpos;
#ifdef DEBUG
	int fields;
#endif
	char *pos, *gpos;
	struct netgrp *grp;
	struct linelist *lp = linehead;

	/*
	 * First, see if the line has already been read in.
	 */
	while (lp) {
		if (!strcmp(group, lp->l_groupname))
			break;
		lp = lp->l_next;
	}
	if (lp == (struct linelist *)0 &&
	    (lp = read_for_group(group)) == (struct linelist *)0)
		return (1);
	if (lp->l_parsed) {
#ifdef DEBUG
		/*
		 * This error message is largely superfluous since the
		 * code handles the error condition successfully, and
		 * spewing it out from inside libc can actually hose
		 * certain programs.
		 */
		warnx("cycle in netgroup %s", lp->l_groupname);
#endif
		return (1);
	} else
		lp->l_parsed = 1;
	pos = lp->l_line;
	/* Watch for null pointer dereferences, dammit! */
	while (pos != NULL && *pos != '\0') {
		if (*pos == '(') {
			grp = (struct netgrp *)malloc(sizeof (struct netgrp));
			bzero((char *)grp, sizeof (struct netgrp));
			grp->ng_next = grouphead.gr;
			grouphead.gr = grp;
			pos++;
			gpos = strsep(&pos, ")");
#ifdef DEBUG
			fields = 0;
#endif
			for (strpos = 0; strpos < 3; strpos++) {
				if ((spos = strsep(&gpos, ","))) {
#ifdef DEBUG
					fields++;
#endif
					while (*spos == ' ' || *spos == '\t')
						spos++;
					if ((epos = strpbrk(spos, " \t"))) {
						*epos = '\0';
						len = epos - spos;
					} else
						len = strlen(spos);
					if (len > 0) {
						grp->ng_str[strpos] =  (char *)
							malloc(len + 1);
						bcopy(spos, grp->ng_str[strpos],
							len + 1);
					}
				} else {
					/*
					 * All other systems I've tested
					 * return NULL for empty netgroup
					 * fields. It's up to user programs
					 * to handle the NULLs appropriately.
					 */
					grp->ng_str[strpos] = NULL;
				}
			}
#ifdef DEBUG
			/*
			 * Note: on other platforms, malformed netgroup
			 * entries are not normally flagged. While we
			 * can catch bad entries and report them, we should
			 * stay silent by default for compatibility's sake.
			 */
			if (fields < 3)
					warnx("bad entry (%s%s%s%s%s) in netgroup \"%s\"",
						grp->ng_str[NG_HOST] == NULL ? "" : grp->ng_str[NG_HOST],
						grp->ng_str[NG_USER] == NULL ? "" : ",",
						grp->ng_str[NG_USER] == NULL ? "" : grp->ng_str[NG_USER],
						grp->ng_str[NG_DOM] == NULL ? "" : ",",
						grp->ng_str[NG_DOM] == NULL ? "" : grp->ng_str[NG_DOM],
						lp->l_groupname);
#endif
		} else {
			spos = strsep(&pos, ", \t");
			if (parse_netgrp(spos))
				continue;
		}
		/* Watch for null pointer dereferences, dammit! */
		if (pos != NULL)
			while (*pos == ' ' || *pos == ',' || *pos == '\t')
				pos++;
	}
	return (0);
}