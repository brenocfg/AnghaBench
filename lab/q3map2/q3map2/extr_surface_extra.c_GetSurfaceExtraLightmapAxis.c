#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int /*<<< orphan*/  lightmapAxis; } ;
typedef  TYPE_1__ surfaceExtra_t ;

/* Variables and functions */
 TYPE_1__* GetSurfaceExtra (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GetSurfaceExtraLightmapAxis( int num, vec3_t lightmapAxis ){
	surfaceExtra_t  *se = GetSurfaceExtra( num );
	VectorCopy( se->lightmapAxis, lightmapAxis );
}