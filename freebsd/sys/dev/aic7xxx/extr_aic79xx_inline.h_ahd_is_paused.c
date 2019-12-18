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
 int /*<<< orphan*/  HCNTRL ; 
 int PAUSE ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
ahd_is_paused(struct ahd_softc *ahd)
{
	return ((ahd_inb(ahd, HCNTRL) & PAUSE) != 0);
}