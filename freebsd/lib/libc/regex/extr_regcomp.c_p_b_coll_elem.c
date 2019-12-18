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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
struct parse {char* next; } ;
struct cname {int /*<<< orphan*/  code; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_ILLSEQ ; 
 int /*<<< orphan*/  SEETWO (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 struct cname* cnames ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static wint_t			/* value of collating element */
p_b_coll_elem(struct parse *p,
	wint_t endc)		/* name ended by endc,']' */
{
	const char *sp = p->next;
	struct cname *cp;
	mbstate_t mbs;
	wchar_t wc;
	size_t clen, len;

	while (MORE() && !SEETWO(endc, ']'))
		NEXT();
	if (!MORE()) {
		SETERROR(REG_EBRACK);
		return(0);
	}
	len = p->next - sp;
	for (cp = cnames; cp->name != NULL; cp++)
		if (strncmp(cp->name, sp, len) == 0 && strlen(cp->name) == len)
			return(cp->code);	/* known name */
	memset(&mbs, 0, sizeof(mbs));
	if ((clen = mbrtowc(&wc, sp, len, &mbs)) == len)
		return (wc);			/* single character */
	else if (clen == (size_t)-1 || clen == (size_t)-2)
		SETERROR(REG_ILLSEQ);
	else
		SETERROR(REG_ECOLLATE);		/* neither */
	return(0);
}