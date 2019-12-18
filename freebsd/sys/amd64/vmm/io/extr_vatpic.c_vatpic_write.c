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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct vatpic {int dummy; } ;
struct atpic {int icw_num; scalar_t__ ready; } ;

/* Variables and functions */
 int ICU_IMR_OFFSET ; 
 int /*<<< orphan*/  VATPIC_LOCK (struct vatpic*) ; 
 int /*<<< orphan*/  VATPIC_UNLOCK (struct vatpic*) ; 
 int vatpic_icw1 (struct vatpic*,struct atpic*,int) ; 
 int vatpic_icw2 (struct vatpic*,struct atpic*,int) ; 
 int vatpic_icw3 (struct vatpic*,struct atpic*,int) ; 
 int vatpic_icw4 (struct vatpic*,struct atpic*,int) ; 
 int /*<<< orphan*/  vatpic_notify_intr (struct vatpic*) ; 
 int vatpic_ocw1 (struct vatpic*,struct atpic*,int) ; 
 int vatpic_ocw2 (struct vatpic*,struct atpic*,int) ; 
 int vatpic_ocw3 (struct vatpic*,struct atpic*,int) ; 

__attribute__((used)) static int
vatpic_write(struct vatpic *vatpic, struct atpic *atpic, bool in, int port,
    int bytes, uint32_t *eax)
{
	int error;
	uint8_t val;

	error = 0;
	val = *eax;

	VATPIC_LOCK(vatpic);

	if (port & ICU_IMR_OFFSET) {
		switch (atpic->icw_num) {
		case 2:
			error = vatpic_icw2(vatpic, atpic, val);
			break;
		case 3:
			error = vatpic_icw3(vatpic, atpic, val);
			break;
		case 4:
			error = vatpic_icw4(vatpic, atpic, val);
			break;
		default:
			error = vatpic_ocw1(vatpic, atpic, val);
			break;
		}
	} else {
		if (val & (1 << 4))
			error = vatpic_icw1(vatpic, atpic, val);

		if (atpic->ready) {
			if (val & (1 << 3))
				error = vatpic_ocw3(vatpic, atpic, val);
			else
				error = vatpic_ocw2(vatpic, atpic, val);
		}
	}

	if (atpic->ready)
		vatpic_notify_intr(vatpic);

	VATPIC_UNLOCK(vatpic);

	return (error);
}