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
struct parse {char* next; } ;
struct cname {char code; int /*<<< orphan*/ * name; } ;
typedef  char RCHAR_T ;

/* Variables and functions */
 scalar_t__ MEMCMP (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  SEETWO (int,char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 size_t STRLEN (int /*<<< orphan*/ *) ; 
 struct cname* cnames ; 

__attribute__((used)) static char			/* value of collating element */
p_b_coll_elem(struct parse *p, int endc)
                         
         			/* name ended by endc,']' */
{
	RCHAR_T *sp = p->next;
	struct cname *cp;
	size_t len;

	while (MORE() && !SEETWO(endc, ']'))
		NEXT();
	if (!MORE()) {
		SETERROR(REG_EBRACK);
		return(0);
	}
	len = p->next - sp;
	for (cp = cnames; cp->name != NULL; cp++)
		if (STRLEN(cp->name) == len && MEMCMP(cp->name, sp, len))
			return(cp->code);	/* known name */
	if (len == 1)
		return(*sp);	/* single character */
	SETERROR(REG_ECOLLATE);			/* neither */
	return(0);
}