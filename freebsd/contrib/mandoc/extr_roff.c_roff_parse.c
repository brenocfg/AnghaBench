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
struct roff {int /*<<< orphan*/  rentab; int /*<<< orphan*/  strtab; int /*<<< orphan*/  reqtab; int /*<<< orphan*/  current_string; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
#define  ROFFDEF_REN 129 
 int ROFFDEF_UNDEF ; 
#define  ROFFDEF_USER 128 
 int ROFF_RENAMED ; 
 int ROFF_USERDEF ; 
 int TOKEN_NONE ; 
 size_t roff_getname (struct roff*,char**,int,int) ; 
 int /*<<< orphan*/  roff_getstrn (struct roff*,char const*,size_t,int*) ; 
 int /*<<< orphan*/  roff_setstrn (int /*<<< orphan*/ *,char const*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roffhash_find (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static enum roff_tok
roff_parse(struct roff *r, char *buf, int *pos, int ln, int ppos)
{
	char		*cp;
	const char	*mac;
	size_t		 maclen;
	int		 deftype;
	enum roff_tok	 t;

	cp = buf + *pos;

	if ('\0' == *cp || '"' == *cp || '\t' == *cp || ' ' == *cp)
		return TOKEN_NONE;

	mac = cp;
	maclen = roff_getname(r, &cp, ln, ppos);

	deftype = ROFFDEF_USER | ROFFDEF_REN;
	r->current_string = roff_getstrn(r, mac, maclen, &deftype);
	switch (deftype) {
	case ROFFDEF_USER:
		t = ROFF_USERDEF;
		break;
	case ROFFDEF_REN:
		t = ROFF_RENAMED;
		break;
	default:
		t = roffhash_find(r->reqtab, mac, maclen);
		break;
	}
	if (t != TOKEN_NONE)
		*pos = cp - buf;
	else if (deftype == ROFFDEF_UNDEF) {
		/* Using an undefined macro defines it to be empty. */
		roff_setstrn(&r->strtab, mac, maclen, "", 0, 0);
		roff_setstrn(&r->rentab, mac, maclen, NULL, 0, 0);
	}
	return t;
}