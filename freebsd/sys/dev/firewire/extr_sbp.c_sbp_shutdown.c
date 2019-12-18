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
struct sbp_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_LOCK (struct sbp_softc*) ; 
 int /*<<< orphan*/  SBP_UNLOCK (struct sbp_softc*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp_logout_all (struct sbp_softc*) ; 

__attribute__((used)) static int
sbp_shutdown(device_t dev)
{
	struct sbp_softc *sbp = ((struct sbp_softc *)device_get_softc(dev));

	SBP_LOCK(sbp);
	sbp_logout_all(sbp);
	SBP_UNLOCK(sbp);
	return (0);
}