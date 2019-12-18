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
struct scb {int /*<<< orphan*/  aic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  aic_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_timeout (struct scb*) ; 
 int /*<<< orphan*/  aic_unlock (int /*<<< orphan*/ ) ; 

void
aic_platform_timeout(void *arg)
{
	struct	scb *scb;
	
	scb = (struct scb *)arg; 
	aic_lock(scb->aic_softc);
	aic_timeout(scb);
	aic_unlock(scb->aic_softc);
}