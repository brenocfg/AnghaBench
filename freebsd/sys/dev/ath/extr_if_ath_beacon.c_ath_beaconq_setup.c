#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {scalar_t__ sc_isedma; struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  qi ;
struct TYPE_4__ {int tqi_qflags; void* tqi_cwmax; void* tqi_cwmin; void* tqi_aifs; } ;
typedef  TYPE_1__ HAL_TXQ_INFO ;

/* Variables and functions */
 int HAL_TXQ_TXDESCINT_ENABLE ; 
 int HAL_TXQ_TXERRINT_ENABLE ; 
 int HAL_TXQ_TXOKINT_ENABLE ; 
 void* HAL_TXQ_USEDEFAULT ; 
 int /*<<< orphan*/  HAL_TX_QUEUE_BEACON ; 
 int ath_hal_setuptxqueue (struct ath_hal*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
ath_beaconq_setup(struct ath_softc *sc)
{
	struct ath_hal *ah = sc->sc_ah;
	HAL_TXQ_INFO qi;

	memset(&qi, 0, sizeof(qi));
	qi.tqi_aifs = HAL_TXQ_USEDEFAULT;
	qi.tqi_cwmin = HAL_TXQ_USEDEFAULT;
	qi.tqi_cwmax = HAL_TXQ_USEDEFAULT;
	/* NB: for dynamic turbo, don't enable any other interrupts */
	qi.tqi_qflags = HAL_TXQ_TXDESCINT_ENABLE;
	if (sc->sc_isedma)
		qi.tqi_qflags |= HAL_TXQ_TXOKINT_ENABLE |
		    HAL_TXQ_TXERRINT_ENABLE;

	return ath_hal_setuptxqueue(ah, HAL_TX_QUEUE_BEACON, &qi);
}