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
typedef  int uint32_t ;
struct vatpic {int dummy; } ;
struct atpic {int mask; scalar_t__ rd_cmd_reg; int service; int request; scalar_t__ poll; } ;

/* Variables and functions */
 int ICU_IMR_OFFSET ; 
 scalar_t__ OCW3_RIS ; 
 int /*<<< orphan*/  VATPIC_LOCK (struct vatpic*) ; 
 int /*<<< orphan*/  VATPIC_UNLOCK (struct vatpic*) ; 
 int vatpic_get_highest_irrpin (struct atpic*) ; 
 int /*<<< orphan*/  vatpic_pin_accepted (struct atpic*,int) ; 

__attribute__((used)) static int
vatpic_read(struct vatpic *vatpic, struct atpic *atpic, bool in, int port,
	    int bytes, uint32_t *eax)
{
	int pin;

	VATPIC_LOCK(vatpic);

	if (atpic->poll) {
		atpic->poll = 0;
		pin = vatpic_get_highest_irrpin(atpic);
		if (pin >= 0) {
			vatpic_pin_accepted(atpic, pin);
			*eax = 0x80 | pin;
		} else {
			*eax = 0;
		}
	} else {
		if (port & ICU_IMR_OFFSET) {
			/* read interrrupt mask register */
			*eax = atpic->mask;
		} else {
			if (atpic->rd_cmd_reg == OCW3_RIS) {
				/* read interrupt service register */
				*eax = atpic->service;
			} else {
				/* read interrupt request register */
				*eax = atpic->request;
			}
		}
	}

	VATPIC_UNLOCK(vatpic);

	return (0);

}