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
struct timecounter {scalar_t__ tc_priv; } ;
struct aml8726_timer_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_TIMER_E_REG ; 
 int CSR_READ_4 (struct aml8726_timer_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
aml8726_get_timecount(struct timecounter *tc)
{
	struct aml8726_timer_softc *sc =
	    (struct aml8726_timer_softc *)tc->tc_priv;

	return CSR_READ_4(sc, AML_TIMER_E_REG);
}