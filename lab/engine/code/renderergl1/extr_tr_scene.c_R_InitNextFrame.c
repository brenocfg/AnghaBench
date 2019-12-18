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
struct TYPE_3__ {scalar_t__ used; } ;
struct TYPE_4__ {TYPE_1__ commands; } ;

/* Variables and functions */
 TYPE_2__* backEndData ; 
 scalar_t__ r_firstSceneDlight ; 
 scalar_t__ r_firstSceneDrawSurf ; 
 scalar_t__ r_firstSceneEntity ; 
 scalar_t__ r_firstScenePoly ; 
 scalar_t__ r_numdlights ; 
 scalar_t__ r_numentities ; 
 scalar_t__ r_numpolys ; 
 scalar_t__ r_numpolyverts ; 

void R_InitNextFrame( void ) {
	backEndData->commands.used = 0;

	r_firstSceneDrawSurf = 0;

	r_numdlights = 0;
	r_firstSceneDlight = 0;

	r_numentities = 0;
	r_firstSceneEntity = 0;

	r_numpolys = 0;
	r_firstScenePoly = 0;

	r_numpolyverts = 0;
}