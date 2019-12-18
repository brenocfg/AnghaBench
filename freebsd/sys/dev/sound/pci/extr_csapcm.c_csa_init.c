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
struct csa_info {scalar_t__ pfie; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_EGPIODR ; 
 int /*<<< orphan*/  BA0_EGPIOPTR ; 
 int EGPIODR_GPOE0 ; 
 int EGPIODR_GPOE2 ; 
 int EGPIOPTR_GPPT0 ; 
 int EGPIOPTR_GPPT2 ; 
 int csa_readio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_setcapturesamplerate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csa_setplaysamplerate (int /*<<< orphan*/ *,int) ; 
 scalar_t__ csa_startdsp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csa_stopcapturedma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopplaydma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csa_init(struct csa_info *csa)
{
	csa_res *resp;

	resp = &csa->res;

	csa->pfie = 0;
	csa_stopplaydma(csa);
	csa_stopcapturedma(csa);

	if (csa_startdsp(resp))
		return (1);

	/* Crank up the power on the DAC and ADC. */
	csa_setplaysamplerate(resp, 8000);
	csa_setcapturesamplerate(resp, 8000);
	/* Set defaults */
	csa_writeio(resp, BA0_EGPIODR, EGPIODR_GPOE0);
	csa_writeio(resp, BA0_EGPIOPTR, EGPIOPTR_GPPT0);
	/* Power up amplifier */
	csa_writeio(resp, BA0_EGPIODR, csa_readio(resp, BA0_EGPIODR) |
		EGPIODR_GPOE2);
	csa_writeio(resp, BA0_EGPIOPTR, csa_readio(resp, BA0_EGPIOPTR) | 
		EGPIOPTR_GPPT2);

	return 0;
}