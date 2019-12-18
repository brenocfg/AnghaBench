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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cpufreq_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_sema ; 

__attribute__((used)) static int
bcm2835_cpufreq_detach(device_t dev)
{

	sema_destroy(&vc_sema);

	return (cpufreq_unregister(dev));
}