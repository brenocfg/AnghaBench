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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_2__ {int /*<<< orphan*/  active; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  apm_display (int) ; 
 TYPE_1__ apm_softc ; 
 int blanked ; 

__attribute__((used)) static int
apm_saver(video_adapter_t *adp, int blank)
{
	if (!apm_softc.initialized || !apm_softc.active)
		return 0;

	if (blank==blanked)
		return 0;

	blanked=blank;

	apm_display(!blanked);

	return 0;
}