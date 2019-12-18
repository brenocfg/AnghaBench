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
typedef  int u_int ;
struct iicrb_pin_access {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* setsda ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* setscl ) (int /*<<< orphan*/ ,int) ;scalar_t__ (* getsda ) (int /*<<< orphan*/ ) ;scalar_t__ (* getscl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int const) ; 
 int IIC_EBUSERR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int) ; 

int
iic_recover_bus(struct iicrb_pin_access *pins)
{
	const u_int timeout_us = 40000;
	const u_int delay_us = 500;
	int i;

	/*
	 * Start with clock and data high.
	 */
	pins->setsda(pins->ctx, 1);
	pins->setscl(pins->ctx, 1);

	/*
	 * At this point, SCL should be high.  If it's not, some slave on the
	 * bus is doing clock-stretching and we should wait a while.  If that
	 * slave is completely locked up there may be no way to recover at all.
	 * We wait up to 40 milliseconds, a seriously pessimistic time (even a
	 * cheap eeprom has a max post-write delay of only 10ms), and also long
	 * enough to allow SMB slaves to timeout normally after 35ms.
	 */
	for (i = 0; i < timeout_us; i += delay_us) {
		if (pins->getscl(pins->ctx))
			break;
		DELAY(delay_us);
	}
	if (i >= timeout_us)
		return (IIC_EBUSERR);

	/*
	 * At this point we should be able to control the clock line.  Some
	 * slave may be part way through a byte transfer, and could be holding
	 * the data line low waiting for more clock pulses to finish the byte.
	 * Cycle the clock until we see the data line go high, but only up to 9
	 * times because if it's not free after 9 clocks we're never going to
	 * win this battle.  We do 9 max because that's a byte plus an ack/nack
	 * bit, after which the slave must not be driving the data line anymore.
	 */
	for (i = 0; ; ++i) {
		if (pins->getsda(pins->ctx))
			break;
		if (i == 9)
			return (IIC_EBUSERR);
		pins->setscl(pins->ctx, 0);
		DELAY(5);
		pins->setscl(pins->ctx, 1);
		DELAY(5);
	}

	/*
	 * At this point we should be in control of both the clock and data
	 * lines, and both lines should be high.  To complete the reset of a
	 * slave that was part way through a transaction, we need to do a
	 * START/STOP sequence, which leaves both lines high at the end.
	 *  - START: SDA transitions high->low while SCL remains high.
	 *  - STOP:  SDA transitions low->high while SCL remains high.
	 * Note that even though the clock line remains high, we transition the
	 * data line no faster than it would change state with a 100khz clock.
	 */
	pins->setsda(pins->ctx, 0);
	DELAY(5);
	pins->setsda(pins->ctx, 1);
	DELAY(5);

	return (0);
}