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
struct mwl_hal_priv {int mh_bastreams; TYPE_1__* mh_streams; } ;
struct mwl_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  const public; } ;
typedef  int /*<<< orphan*/  MWL_HAL_BASTREAM ;

/* Variables and functions */
 struct mwl_hal_priv* MWLPRIV (struct mwl_hal*) ; 
 int MWL_BASTREAMS_MAX ; 

const MWL_HAL_BASTREAM *
mwl_hal_bastream_lookup(struct mwl_hal *mh0, int s)
{
	struct mwl_hal_priv *mh = MWLPRIV(mh0);

	if (!(0 <= s && s < MWL_BASTREAMS_MAX))
		return NULL;
	if (mh->mh_bastreams & (1<<s))
		return NULL;
	return &mh->mh_streams[s].public;
}