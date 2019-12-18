#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int accelx; int remainx; int accely; int remainy; } ;

/* Variables and functions */
 int lround (float) ; 
 TYPE_1__ rodent ; 

__attribute__((used)) static void
linacc(int dx, int dy, int *movex, int *movey)
{
    float fdx, fdy;

    if (dx == 0 && dy == 0) {
	*movex = *movey = 0;
	return;
    }
    fdx = dx * rodent.accelx + rodent.remainx;
    fdy = dy * rodent.accely + rodent.remainy;
    *movex = lround(fdx);
    *movey = lround(fdy);
    rodent.remainx = fdx - *movex;
    rodent.remainy = fdy - *movey;
}