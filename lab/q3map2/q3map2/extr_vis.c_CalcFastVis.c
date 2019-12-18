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
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  portalflood; int /*<<< orphan*/  portalvis; } ;

/* Variables and functions */
 int numportals ; 
 TYPE_1__* portals ; 
 int /*<<< orphan*/  stat_done ; 

void CalcFastVis( void ){
	int i;

	// fastvis just uses mightsee for a very loose bound
	for ( i = 0 ; i < numportals * 2 ; i++ )
	{
		portals[i].portalvis = portals[i].portalflood;
		portals[i].status = stat_done;
	}
}