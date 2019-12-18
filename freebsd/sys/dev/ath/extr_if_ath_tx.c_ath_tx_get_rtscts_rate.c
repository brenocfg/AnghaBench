#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  shortPreamble; int /*<<< orphan*/  rateCode; } ;
typedef  TYPE_2__ HAL_RATE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static uint8_t
ath_tx_get_rtscts_rate(struct ath_hal *ah, const HAL_RATE_TABLE *rt,
    int cix, int shortPreamble)
{
	uint8_t ctsrate;

	/*
	 * CTS transmit rate is derived from the transmit rate
	 * by looking in the h/w rate table.  We must also factor
	 * in whether or not a short preamble is to be used.
	 */
	/* NB: cix is set above where RTS/CTS is enabled */
	KASSERT(cix != 0xff, ("cix not setup"));
	ctsrate = rt->info[cix].rateCode;

	/* XXX this should only matter for legacy rates */
	if (shortPreamble)
		ctsrate |= rt->info[cix].shortPreamble;

	return (ctsrate);
}