#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {TYPE_1__* info; } ;
struct TYPE_5__ {int /*<<< orphan*/  rateCode; } ;
typedef  TYPE_2__ HAL_RATE_TABLE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int HT_RC_2_STREAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_HT_RATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ath_computedur_ht (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_computetxtime (struct ath_hal*,TYPE_2__ const*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
ath_hal_pkt_txtime(struct ath_hal *ah, const HAL_RATE_TABLE *rates, uint32_t frameLen,
    uint16_t rateix, HAL_BOOL isht40, HAL_BOOL shortPreamble,
    HAL_BOOL includeSifs)
{
	uint8_t rc;
	int numStreams;

	rc = rates->info[rateix].rateCode;

	/* Legacy rate? Return the old way */
	if (! IS_HT_RATE(rc))
		return ath_hal_computetxtime(ah, rates, frameLen, rateix,
		    shortPreamble, includeSifs);

	/* 11n frame - extract out the number of spatial streams */
	numStreams = HT_RC_2_STREAMS(rc);
	KASSERT(numStreams > 0 && numStreams <= 4,
	    ("number of spatial streams needs to be 1..3: MCS rate 0x%x!",
	    rateix));

	/* XXX TODO: Add SIFS */
	return ath_computedur_ht(frameLen, rc, numStreams, isht40,
	    shortPreamble);
}