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
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_intr (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*) ; 

void
ahc_platform_intr(void *arg)
{
	struct	ahc_softc *ahc;

	ahc = (struct ahc_softc *)arg; 
	ahc_lock(ahc);
	ahc_intr(ahc);
	ahc_unlock(ahc);
}