#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  priv_nf; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct TYPE_11__ {TYPE_2__ nf_cal_hist; } ;
struct TYPE_7__ {TYPE_3__ base; } ;
struct TYPE_10__ {TYPE_1__ nf_cal_hist; } ;
typedef  TYPE_3__ HAL_NFCAL_BASE ;
typedef  TYPE_4__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 TYPE_6__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
ar9300_get_nf_hist_base(struct ath_hal *ah, HAL_CHANNEL_INTERNAL *chan,
    int is_scan, int16_t nf[])
{
    HAL_NFCAL_BASE *h_base;

#ifdef ATH_NF_PER_CHAN
    h_base = &chan->nf_cal_hist.base;
#else
    if (is_scan) {
        /*
         * The channel we are currently on is not the home channel,
         * so we shouldn't use the home channel NF buffer's values on
         * this channel.  Instead, use the NF single value already
         * read for this channel.  (Or, if we haven't read the NF for
         * this channel yet, the SW default for this chip/band will
         * be used.)
         */
        h_base = &chan->nf_cal_hist.base;
    } else {
        /* use the home channel NF info */
        h_base = &AH_PRIVATE(ah)->nf_cal_hist.base;
    }
#endif
    OS_MEMCPY(nf, h_base->priv_nf, sizeof(h_base->priv_nf));
}