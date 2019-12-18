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
struct TYPE_3__ {int lastch; int /*<<< orphan*/  state; int /*<<< orphan*/  str; scalar_t__ cnt; int /*<<< orphan*/  cclass; } ;
typedef  TYPE_1__ STR ;

/* Variables and functions */
 int /*<<< orphan*/  CCLASS ; 
 int /*<<< orphan*/  CCLASS_LOWER ; 
 int /*<<< orphan*/  CCLASS_UPPER ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wctype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
genclass(STR *s)
{

	if ((s->cclass = wctype(s->str)) == 0)
		errx(1, "unknown class %s", s->str);
	s->cnt = 0;
	s->lastch = -1;		/* incremented before check in next() */
	if (strcmp(s->str, "upper") == 0)
		s->state = CCLASS_UPPER;
	else if (strcmp(s->str, "lower") == 0)
		s->state = CCLASS_LOWER;
	else
		s->state = CCLASS;
}