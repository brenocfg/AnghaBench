#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* areasettings; } ;
struct TYPE_3__ {int contents; } ;

/* Variables and functions */
 int AREACONTENTS_LAVA ; 
 TYPE_2__ aasworld ; 

int AAS_AreaLava(int areanum)
{
	return (aasworld.areasettings[areanum].contents & AREACONTENTS_LAVA);
}