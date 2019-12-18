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
typedef  int /*<<< orphan*/  wctype_t ;
typedef  int /*<<< orphan*/  uch ;
struct parse {char* next; } ;
typedef  int /*<<< orphan*/  cset ;
typedef  int /*<<< orphan*/  clname ;

/* Variables and functions */
 int /*<<< orphan*/  CHaddtype (struct parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 scalar_t__ PEEK () ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  wctype (char*) ; 

__attribute__((used)) static void
p_b_cclass(struct parse *p, cset *cs)
{
	const char *sp = p->next;
	size_t len;
	wctype_t wct;
	char clname[16];

	while (MORE() && isalpha((uch)PEEK()))
		NEXT();
	len = p->next - sp;
	if (len >= sizeof(clname) - 1) {
		SETERROR(REG_ECTYPE);
		return;
	}
	memcpy(clname, sp, len);
	clname[len] = '\0';
	if ((wct = wctype(clname)) == 0) {
		SETERROR(REG_ECTYPE);
		return;
	}
	CHaddtype(p, cs, wct);
}