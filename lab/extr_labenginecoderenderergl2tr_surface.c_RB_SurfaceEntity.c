#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceType_t ;
struct TYPE_6__ {TYPE_2__* currentEntity; } ;
struct TYPE_4__ {int reType; } ;
struct TYPE_5__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_SurfaceAxis () ; 
 int /*<<< orphan*/  RB_SurfaceBeam () ; 
 int /*<<< orphan*/  RB_SurfaceLightningBolt () ; 
 int /*<<< orphan*/  RB_SurfaceRailCore () ; 
 int /*<<< orphan*/  RB_SurfaceRailRings () ; 
 int /*<<< orphan*/  RB_SurfaceSprite () ; 
#define  RT_BEAM 132 
#define  RT_LIGHTNING 131 
#define  RT_RAIL_CORE 130 
#define  RT_RAIL_RINGS 129 
#define  RT_SPRITE 128 
 TYPE_3__ backEnd ; 

__attribute__((used)) static void RB_SurfaceEntity( surfaceType_t *surfType ) {
	switch( backEnd.currentEntity->e.reType ) {
	case RT_SPRITE:
		RB_SurfaceSprite();
		break;
	case RT_BEAM:
		RB_SurfaceBeam();
		break;
	case RT_RAIL_CORE:
		RB_SurfaceRailCore();
		break;
	case RT_RAIL_RINGS:
		RB_SurfaceRailRings();
		break;
	case RT_LIGHTNING:
		RB_SurfaceLightningBolt();
		break;
	default:
		RB_SurfaceAxis();
		break;
	}
}