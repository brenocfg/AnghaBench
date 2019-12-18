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
struct vatpic {int* elc; struct atpic* atpic; } ;
struct atpic {int* acnt; int request; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VATPIC_CTR1 (struct vatpic*,char*,int) ; 
 int /*<<< orphan*/  VATPIC_CTR2 (struct vatpic*,char*,int,int) ; 
 int /*<<< orphan*/  VATPIC_CTR3 (struct vatpic*,char*,int,char*,int) ; 
 int VATPIC_LOCKED (struct vatpic*) ; 
 int /*<<< orphan*/  vatpic_notify_intr (struct vatpic*) ; 

__attribute__((used)) static void
vatpic_set_pinstate(struct vatpic *vatpic, int pin, bool newstate)
{
	struct atpic *atpic;
	int oldcnt, newcnt;
	bool level;

	KASSERT(pin >= 0 && pin < 16,
	    ("vatpic_set_pinstate: invalid pin number %d", pin));
	KASSERT(VATPIC_LOCKED(vatpic),
	    ("vatpic_set_pinstate: vatpic is not locked"));

	atpic = &vatpic->atpic[pin >> 3];

	oldcnt = atpic->acnt[pin & 0x7];
	if (newstate)
		atpic->acnt[pin & 0x7]++;
	else
		atpic->acnt[pin & 0x7]--;
	newcnt = atpic->acnt[pin & 0x7];

	if (newcnt < 0) {
		VATPIC_CTR2(vatpic, "atpic pin%d: bad acnt %d", pin, newcnt);
	}

	level = ((vatpic->elc[pin >> 3] & (1 << (pin & 0x7))) != 0);

	if ((oldcnt == 0 && newcnt == 1) || (newcnt > 0 && level == true)) {
		/* rising edge or level */
		VATPIC_CTR1(vatpic, "atpic pin%d: asserted", pin);
		atpic->request |= (1 << (pin & 0x7));
	} else if (oldcnt == 1 && newcnt == 0) {
		/* falling edge */
		VATPIC_CTR1(vatpic, "atpic pin%d: deasserted", pin);
		if (level)
			atpic->request &= ~(1 << (pin & 0x7));
	} else {
		VATPIC_CTR3(vatpic, "atpic pin%d: %s, ignored, acnt %d",
		    pin, newstate ? "asserted" : "deasserted", newcnt);
	}

	vatpic_notify_intr(vatpic);
}