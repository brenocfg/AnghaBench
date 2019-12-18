#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rxstatus_offset; int /*<<< orphan*/  rxstatus_numwords; int /*<<< orphan*/  rxctl_offset; int /*<<< orphan*/  rxctl_numwords; int /*<<< orphan*/  txstatus_offset; int /*<<< orphan*/  txstatus_numwords; int /*<<< orphan*/  txctl_offset; int /*<<< orphan*/  txctl_numwords; } ;
typedef  TYPE_1__ HAL_DESC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  RXCTL_NUMWORDS (struct ath_hal*) ; 
 int /*<<< orphan*/  RXCTL_OFFSET (struct ath_hal*) ; 
 int /*<<< orphan*/  RXSTATUS_NUMWORDS (struct ath_hal*) ; 
 int /*<<< orphan*/  RXSTATUS_OFFSET (struct ath_hal*) ; 
 int /*<<< orphan*/  TXCTL_NUMWORDS (struct ath_hal*) ; 
 int /*<<< orphan*/  TXCTL_OFFSET (struct ath_hal*) ; 
 int /*<<< orphan*/  TXSTATUS_NUMWORDS (struct ath_hal*) ; 
 int /*<<< orphan*/  TXSTATUS_OFFSET (struct ath_hal*) ; 

void
ar9300_get_desc_info(struct ath_hal *ah, HAL_DESC_INFO *desc_info)
{
    desc_info->txctl_numwords = TXCTL_NUMWORDS(ah);
    desc_info->txctl_offset = TXCTL_OFFSET(ah);
    desc_info->txstatus_numwords = TXSTATUS_NUMWORDS(ah);
    desc_info->txstatus_offset = TXSTATUS_OFFSET(ah);

    desc_info->rxctl_numwords = RXCTL_NUMWORDS(ah);
    desc_info->rxctl_offset = RXCTL_OFFSET(ah);
    desc_info->rxstatus_numwords = RXSTATUS_NUMWORDS(ah);
    desc_info->rxstatus_offset = RXSTATUS_OFFSET(ah);
}