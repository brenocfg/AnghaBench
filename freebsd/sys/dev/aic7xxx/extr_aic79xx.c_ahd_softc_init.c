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
struct ahd_softc {int /*<<< orphan*/  pause; scalar_t__ unpause; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAUSE ; 

int
ahd_softc_init(struct ahd_softc *ahd)
{

	ahd->unpause = 0;
	ahd->pause = PAUSE; 
	return (0);
}