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

/* Variables and functions */
 int /*<<< orphan*/  cpu_park_loop () ; 
 int /*<<< orphan*/  local_daif_mask () ; 
 int /*<<< orphan*/  sdei_mask_local_cpu () ; 
 int /*<<< orphan*/  set_cpu_online (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void local_cpu_stop(void)
{
	set_cpu_online(smp_processor_id(), false);

	local_daif_mask();
	sdei_mask_local_cpu();
	cpu_park_loop();
}