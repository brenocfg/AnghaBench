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
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsec_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ubsec_shutdown(device_t dev)
{
#ifdef notyet
	ubsec_stop(device_get_softc(dev));
#endif
	return (0);
}