#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  color; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ srfFlare_t ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int /*<<< orphan*/  fogNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_AddFlare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* r_flares ; 
 TYPE_2__ tess ; 

__attribute__((used)) static void RB_SurfaceFlare(srfFlare_t *surf)
{
	if (r_flares->integer)
		RB_AddFlare(surf, tess.fogNum, surf->origin, surf->color, surf->normal);
}