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
typedef  int /*<<< orphan*/  uch ;
struct parse {char* next; } ;
struct cclass {char* name; char* chars; char* multis; } ;
typedef  int /*<<< orphan*/  cset ;

/* Variables and functions */
 int /*<<< orphan*/  CHadd (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  MCadd (struct parse*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 scalar_t__ PEEK () ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 struct cclass* cclasses ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

__attribute__((used)) static void
p_b_cclass(struct parse *p, cset *cs)
{
	char *sp = p->next;
	struct cclass *cp;
	size_t len;
	const char *u;
	char c;

	while (MORE() && isalpha((uch)PEEK()))
		NEXT();
	len = p->next - sp;
	for (cp = cclasses; cp->name != NULL; cp++)
		if (strncmp(cp->name, sp, len) == 0 && cp->name[len] == '\0')
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