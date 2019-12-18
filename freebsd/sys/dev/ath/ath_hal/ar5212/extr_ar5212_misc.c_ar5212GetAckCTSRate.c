#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_staId1Defaults; } ;

/* Variables and functions */
 TYPE_1__* AH5212 (struct ath_hal*) ; 
 int AR_STA_ID1_ACKCTS_6MB ; 

u_int
ar5212GetAckCTSRate(struct ath_hal *ah)
{
	return ((AH5212(ah)->ah_staId1Defaults & AR_STA_ID1_ACKCTS_6MB) == 0);
}