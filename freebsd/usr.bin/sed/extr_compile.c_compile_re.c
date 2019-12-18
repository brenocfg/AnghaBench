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
struct TYPE_6__ {scalar_t__ re_nsub; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int REG_ICASE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname ; 
 int /*<<< orphan*/  linenum ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ maxnsub ; 
 int regcomp (TYPE_1__*,char*,int) ; 
 int rflags ; 
 int /*<<< orphan*/  strregerror (int,TYPE_1__*) ; 

__attribute__((used)) static regex_t *
compile_re(char *re, int case_insensitive)
{
	regex_t *rep;
	int eval, flags;


	flags = rflags;
	if (case_insensitive)
		flags |= REG_ICASE;
	if ((rep = malloc(sizeof(regex_t))) == NULL)
		err(1, "malloc");
	if ((eval = regcomp(rep, re, flags)) != 0)
		errx(1, "%lu: %s: RE error: %s",
				linenum, fname, strregerror(eval, rep));
	if (maxnsub < rep->re_nsub)
		maxnsub = rep->re_nsub;
	return (rep);
}