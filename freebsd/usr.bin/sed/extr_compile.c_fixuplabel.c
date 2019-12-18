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
struct TYPE_2__ {struct s_command* c; } ;
struct s_command {int code; struct s_command* next; TYPE_1__ u; int /*<<< orphan*/ * t; } ;

/* Variables and functions */
 int /*<<< orphan*/  appendnum ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct s_command* findlabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fname ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenum ; 

__attribute__((used)) static void
fixuplabel(struct s_command *cp, struct s_command *end)
{

	for (; cp != end; cp = cp->next)
		switch (cp->code) {
		case 'a':
		case 'r':
			appendnum++;
			break;
		case 'b':
		case 't':
			/* Resolve branch target. */
			if (cp->t == NULL) {
				cp->u.c = NULL;
				break;
			}
			if ((cp->u.c = findlabel(cp->t)) == NULL)
				errx(1, "%lu: %s: undefined label '%s'", linenum, fname, cp->t);
			free(cp->t);
			break;
		case '{':
			/* Do interior commands. */
			fixuplabel(cp->u.c, cp->next);
			break;
		}
}