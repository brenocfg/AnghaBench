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
struct ahd_softc {int features; } ;

/* Variables and functions */
 int AHD_NEW_DFCNTRL_OPTS ; 

__attribute__((used)) static int
ahd_patch18_func(struct ahd_softc *ahd)
{
	return ((ahd->features & AHD_NEW_DFCNTRL_OPTS) != 0);
}