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
 TYPE_1__ apm_softc ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
apm_init(video_adapter_t *adp)
{
	if (!apm_softc.initialized || !apm_softc.active)
		printf("WARNING: apm_saver module requires apm enabled\n");
	return 0;
}