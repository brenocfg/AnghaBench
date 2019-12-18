#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_9__ {scalar_t__ re_nsub; } ;
typedef  TYPE_2__ regex_t ;

/* Variables and functions */
#define  REG_NOMATCH 128 
 int /*<<< orphan*/  exit_regerror (int,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  pbnum (int) ; 
 int /*<<< orphan*/  pbunsigned (int /*<<< orphan*/ ) ; 
 int regexec (TYPE_2__*,char const*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_regexpindex(const char *string, regex_t *re, const char *source,
    regmatch_t *pm)
{
	int error;

	switch(error = regexec(re, string, re->re_nsub+1, pm, 0)) {
	case 0:
		pbunsigned(pm[0].rm_so);
		break;
	case REG_NOMATCH:
		pbnum(-1);
		break;
	default:
		exit_regerror(error, re, source);
	}
}