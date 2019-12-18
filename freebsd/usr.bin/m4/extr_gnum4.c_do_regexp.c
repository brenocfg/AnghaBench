#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regmatch_t ;
struct TYPE_6__ {scalar_t__ re_nsub; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
#define  REG_NOMATCH 128 
 int /*<<< orphan*/  add_replace (char const*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_regerror (int,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  getstring () ; 
 int /*<<< orphan*/  pbstr (int /*<<< orphan*/ ) ; 
 int regexec (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_regexp(const char *string, regex_t *re, const char *source,
    const char *replace, regmatch_t *pm)
{
	int error;

	switch(error = regexec(re, string, re->re_nsub+1, pm, 0)) {
	case 0:
		add_replace(string, re, replace, pm);
		pbstr(getstring());
		break;
	case REG_NOMATCH:
		break;
	default:
		exit_regerror(error, re, source);
	}
}