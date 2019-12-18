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
struct ess_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ess_reset_dsp (struct ess_info*) ; 
 scalar_t__ mixer_reinit (int /*<<< orphan*/ ) ; 
 struct ess_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ess_resume(device_t dev)
{
	struct ess_info *sc;

	sc = pcm_getdevinfo(dev);

	if (ess_reset_dsp(sc)) {
		device_printf(dev, "unable to reset DSP at resume\n");
		return ENXIO;
	}

	if (mixer_reinit(dev)) {
		device_printf(dev, "unable to reinitialize mixer at resume\n");
		return ENXIO;
	}

	return 0;
}