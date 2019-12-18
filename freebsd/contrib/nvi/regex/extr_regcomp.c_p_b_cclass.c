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
struct parse {int /*<<< orphan*/ * next; } ;
struct cclass {char* chars; char* multis; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  cset ;
typedef  int /*<<< orphan*/  RCHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHadd (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  MCadd (struct parse*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  MEMCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  PEEK () ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 size_t STRLEN (int /*<<< orphan*/ *) ; 
 struct cclass* cclasses ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
p_b_cclass(struct parse *p, cset *cs)
{
	RCHAR_T *sp = p->next;
	struct cclass *cp;
	size_t len;
	const char *u;
	char c;

	while (MORE() && isalpha(PEEK()))
		NEXT();
	len = p->next - sp;
	for (cp = cclasses; cp->name != NULL; cp++)
		if (STRLEN(cp->name) == len && !MEMCMP(cp->name, sp, len))
			break;
	if (cp->name == NULL) {
		/* oops, didn't find it */
		SETERROR(REG_ECTYPE);
		return;
	}

	u = cp->chars;
	while ((c = *u++) != '\0')
		CHadd(cs, c);
	for (u = cp->multis; *u != '\0'; u += strlen(u) + 1)
		MCadd(p, cs, u);
}