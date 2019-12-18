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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ bChannel; int tPowerFlag; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_1__ CAL_CTL_EDGES ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 scalar_t__ AR5416_MAX_RATE_POWER ; 
 int AR5416_NUM_BAND_EDGES ; 
 int CAL_CTL_EDGES_FLAG ; 
 int /*<<< orphan*/  CAL_CTL_EDGES_POWER ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fbin2freq (scalar_t__,int /*<<< orphan*/ ) ; 

uint16_t
ar5416GetMaxEdgePower(uint16_t freq, CAL_CTL_EDGES *pRdEdgesPower, HAL_BOOL is2GHz)
{
    uint16_t twiceMaxEdgePower = AR5416_MAX_RATE_POWER;
    int      i;

    /* Get the edge power */
    for (i = 0; (i < AR5416_NUM_BAND_EDGES) && (pRdEdgesPower[i].bChannel != AR5416_BCHAN_UNUSED) ; i++) {
        /*
         * If there's an exact channel match or an inband flag set
         * on the lower channel use the given rdEdgePower
         */
        if (freq == fbin2freq(pRdEdgesPower[i].bChannel, is2GHz)) {
            twiceMaxEdgePower = MS(pRdEdgesPower[i].tPowerFlag, CAL_CTL_EDGES_POWER);
            break;
        } else if ((i > 0) && (freq < fbin2freq(pRdEdgesPower[i].bChannel, is2GHz))) {
            if (fbin2freq(pRdEdgesPower[i - 1].bChannel, is2GHz) < freq && (pRdEdgesPower[i - 1].tPowerFlag & CAL_CTL_EDGES_FLAG) != 0) {
                twiceMaxEdgePower = MS(pRdEdgesPower[i - 1].tPowerFlag, CAL_CTL_EDGES_POWER);
            }
            /* Leave loop - no more affecting edges possible in this monotonic increasing list */
            break;
        }
    }
    HALASSERT(twiceMaxEdgePower > 0);
    return twiceMaxEdgePower;
}