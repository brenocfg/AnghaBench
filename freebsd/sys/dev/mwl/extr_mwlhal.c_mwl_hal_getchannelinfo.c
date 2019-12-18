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
struct TYPE_3__ {scalar_t__ freqLow; scalar_t__ freqHigh; } ;
struct mwl_hal_priv {TYPE_1__ mh_40M_5G; TYPE_1__ mh_20M_5G; TYPE_1__ mh_40M; TYPE_1__ mh_20M; } ;
struct mwl_hal {int dummy; } ;
typedef  TYPE_1__ MWL_HAL_CHANNELINFO ;

/* Variables and functions */
 int EINVAL ; 
 struct mwl_hal_priv* MWLPRIV (struct mwl_hal*) ; 
 int MWL_CH_20_MHz_WIDTH ; 
#define  MWL_FREQ_BAND_2DOT4GHZ 129 
#define  MWL_FREQ_BAND_5GHZ 128 

int
mwl_hal_getchannelinfo(struct mwl_hal *mh0, int band, int chw,
	const MWL_HAL_CHANNELINFO **ci)
{
	struct mwl_hal_priv *mh = MWLPRIV(mh0);

	switch (band) {
	case MWL_FREQ_BAND_2DOT4GHZ:
		*ci = (chw == MWL_CH_20_MHz_WIDTH) ? &mh->mh_20M : &mh->mh_40M;
		break;
	case MWL_FREQ_BAND_5GHZ:
		*ci = (chw == MWL_CH_20_MHz_WIDTH) ?
		     &mh->mh_20M_5G : &mh->mh_40M_5G;
		break;
	default:
		return EINVAL;
	}
	return ((*ci)->freqLow == (*ci)->freqHigh) ? EINVAL : 0;
}