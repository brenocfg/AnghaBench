#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_9__ {char* fts_path; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/ * re_data; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ FTSENT ;

/* Variables and functions */
 int F_IGNCASE ; 
 int LINE_MAX ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  REG_STARTEND ; 
 int /*<<< orphan*/  errx (int,char*,char*,char*) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int
f_regex(PLAN *plan, FTSENT *entry)
{
	char *str;
	int len;
	regex_t *pre;
	regmatch_t pmatch;
	int errcode;
	char errbuf[LINE_MAX];
	int matched;

	pre = plan->re_data;
	str = entry->fts_path;
	len = strlen(str);
	matched = 0;

	pmatch.rm_so = 0;
	pmatch.rm_eo = len;

	errcode = regexec(pre, str, 1, &pmatch, REG_STARTEND);

	if (errcode != 0 && errcode != REG_NOMATCH) {
		regerror(errcode, pre, errbuf, sizeof errbuf);
		errx(1, "%s: %s",
		     plan->flags & F_IGNCASE ? "-iregex" : "-regex", errbuf);
	}

	if (errcode == 0 && pmatch.rm_so == 0 && pmatch.rm_eo == len)
		matched = 1;

	return matched;
}