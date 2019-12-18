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
struct agg_info {int playchns; int active; int /*<<< orphan*/  rch; scalar_t__ pch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  agg_lock (struct agg_info*) ; 
 int /*<<< orphan*/  agg_power (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (struct agg_info*) ; 
 int /*<<< orphan*/  aggch_start_adc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aggch_start_dac (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mixer_reinit (int /*<<< orphan*/ ) ; 
 struct agg_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerstate_init ; 

__attribute__((used)) static int
agg_resume(device_t dev)
{
	int i;
	struct agg_info *ess = pcm_getdevinfo(dev);

	for (i = 0; i < ess->playchns; i++)
		if (ess->active & (1 << i))
			aggch_start_dac(ess->pch + i);
	if (ess->active & (1 << i))
		aggch_start_adc(&ess->rch);

	agg_lock(ess);
	if (!ess->active)
		agg_power(ess, powerstate_init);
	agg_unlock(ess);

	if (mixer_reinit(dev)) {
		device_printf(dev, "unable to reinitialize the mixer\n");
		return ENXIO;
	}

	return 0;
}