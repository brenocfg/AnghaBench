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
struct parse {scalar_t__ error; } ;
typedef  scalar_t__ sopno ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD (scalar_t__) ; 
 int /*<<< orphan*/  ASTERN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HERE () ; 
 int /*<<< orphan*/  INSERT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MORE () ; 
 int /*<<< orphan*/  OCH_ ; 
 int /*<<< orphan*/  OOR1 ; 
 int /*<<< orphan*/  OOR2 ; 
 int /*<<< orphan*/  O_CH ; 
 char PEEK () ; 
 int /*<<< orphan*/  RECLIMIT ; 
 int /*<<< orphan*/  REG_EMPTY ; 
 scalar_t__ REG_ESPACE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SEE (int) ; 
 scalar_t__ THERE () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  p_ere_exp (struct parse*,size_t) ; 

__attribute__((used)) static void
p_ere(struct parse *p, int stop, size_t reclimit)
         			/* character this ERE should end at */
{
	char c;
	sopno prevback = 0;
	sopno prevfwd = 0;
	sopno conc;
	int first = 1;		/* is this the first alternative? */

	if (reclimit++ > RECLIMIT || p->error == REG_ESPACE) {
		p->error = REG_ESPACE;
		return;
	}

	for (;;) {
		/* do a bunch of concatenated expressions */
		conc = HERE();
		while (MORE() && (c = PEEK()) != '|' && c != stop)
			p_ere_exp(p, reclimit);
		(void)REQUIRE(HERE() != conc, REG_EMPTY);	/* require nonempty */

		if (!EAT('|'))
			break;		/* NOTE BREAK OUT */

		if (first) {
			INSERT(OCH_, conc);	/* offset is wrong */
			prevfwd = conc;
			prevback = conc;
			first = 0;
		}
		ASTERN(OOR1, prevback);
		prevback = THERE();
		AHEAD(prevfwd);			/* fix previous offset */
		prevfwd = HERE();
		EMIT(OOR2, 0);			/* offset is very wrong */
	}

	if (!first) {		/* tail-end fixups */
		AHEAD(prevfwd);
		ASTERN(O_CH, prevback);
	}

	assert(!MORE() || SEE(stop));
}