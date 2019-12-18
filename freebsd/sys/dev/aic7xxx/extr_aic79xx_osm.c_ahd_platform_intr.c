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
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_intr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*) ; 

void
ahd_platform_intr(void *arg)
{
	struct	ahd_softc *ahd;

	ahd = (struct ahd_softc *)arg; 
	ahd_lock(ahd);
	ahd_intr(ahd);
	ahd_unlock(ahd);
}