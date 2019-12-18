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
struct sbuf {int dummy; } ;
typedef  scalar_t__ nl_item ;

/* Variables and functions */
 scalar_t__ ABDAY_1 ; 
 scalar_t__ ABDAY_7 ; 
 scalar_t__ ABMON_1 ; 
 scalar_t__ ABMON_12 ; 
 scalar_t__ AM_STR ; 
 scalar_t__ DAY_1 ; 
 scalar_t__ DAY_7 ; 
#define  KW_TIME_ABDAY 132 
#define  KW_TIME_ABMON 131 
#define  KW_TIME_AM_PM 130 
#define  KW_TIME_DAY 129 
#define  KW_TIME_MON 128 
 scalar_t__ MON_1 ; 
 scalar_t__ MON_12 ; 
 scalar_t__ PM_STR ; 
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* nl_langinfo (scalar_t__) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
kwval_ltime(int id)
{
	char *rval;
	struct sbuf *kwsbuf;
	nl_item i, s_item = 0, e_item = 0;

	switch (id) {
	case KW_TIME_DAY:
		s_item = DAY_1;
		e_item = DAY_7;
		break;
	case KW_TIME_ABDAY:
		s_item = ABDAY_1;
		e_item = ABDAY_7;
		break;
	case KW_TIME_MON:
		s_item = MON_1;
		e_item = MON_12;
		break;
	case KW_TIME_ABMON:
		s_item = ABMON_1;
		e_item = ABMON_12;
		break;
	case KW_TIME_AM_PM:
		if (asprintf(&rval, "%s;%s",
		    nl_langinfo(AM_STR),
		    nl_langinfo(PM_STR)) == -1)
			err(1, "asprintf");
		return (rval);
	}

	kwsbuf = sbuf_new_auto();
	if (kwsbuf == NULL)
		err(1, "sbuf");
	for (i = s_item; i <= e_item; i++) {
		(void) sbuf_cat(kwsbuf, nl_langinfo(i));
		if (i != e_item)
			(void) sbuf_cat(kwsbuf, ";");
	}
	(void) sbuf_finish(kwsbuf);
	rval = strdup(sbuf_data(kwsbuf));
	if (rval == NULL)
		err(1, "strdup");
	sbuf_delete(kwsbuf);
	return (rval);
}