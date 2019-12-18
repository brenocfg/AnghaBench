#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tval; int /*<<< orphan*/  sval; int /*<<< orphan*/  fval; } ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 int /*<<< orphan*/  NUM ; 
 int /*<<< orphan*/  STR ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 char* qstring (char*,char) ; 
 int /*<<< orphan*/  setsval (TYPE_1__*,char*) ; 
 TYPE_1__* setsymtab (char*,char*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symtab ; 

void setclvar(char *s)	/* set var=value from s */
{
	char *p;
	Cell *q;

	for (p=s; *p != '='; p++)
		;
	*p++ = 0;
	p = qstring(p, '\0');
	q = setsymtab(s, p, 0.0, STR, symtab);
	setsval(q, p);
	if (is_number(q->sval)) {
		q->fval = atof(q->sval);
		q->tval |= NUM;
	}
	   dprintf( ("command line set %s to |%s|\n", s, p) );
}