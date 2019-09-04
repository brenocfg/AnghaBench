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
struct kwsmatch {int* size; } ;
struct grep_pat {int /*<<< orphan*/  kws; } ;
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int REG_NOMATCH ; 
 size_t kwsexec (int /*<<< orphan*/ ,char*,int,struct kwsmatch*) ; 

__attribute__((used)) static int fixmatch(struct grep_pat *p, char *line, char *eol,
		    regmatch_t *match)
{
	struct kwsmatch kwsm;
	size_t offset = kwsexec(p->kws, line, eol - line, &kwsm);
	if (offset == -1) {
		match->rm_so = match->rm_eo = -1;
		return REG_NOMATCH;
	} else {
		match->rm_so = offset;
		match->rm_eo = match->rm_so + kwsm.size[0];
		return 0;
	}
}