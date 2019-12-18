#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cubemapIndex; int /*<<< orphan*/  fogIndex; int /*<<< orphan*/  shader; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ msurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_AddDrawSurf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ R_CullSurface (TYPE_1__*) ; 
 int R_DlightSurface (TYPE_1__*,int) ; 
 int R_PshadowSurface (TYPE_1__*,int) ; 

__attribute__((used)) static void R_AddWorldSurface( msurface_t *surf, int dlightBits, int pshadowBits ) {
	// FIXME: bmodel fog?

	// try to cull before dlighting or adding
	if ( R_CullSurface( surf ) ) {
		return;
	}

	// check for dlighting
	/*if ( dlightBits ) */{
		dlightBits = R_DlightSurface( surf, dlightBits );
		dlightBits = ( dlightBits != 0 );
	}

	// check for pshadows
	/*if ( pshadowBits ) */{
		pshadowBits = R_PshadowSurface( surf, pshadowBits);
		pshadowBits = ( pshadowBits != 0 );
	}

	R_AddDrawSurf( surf->data, surf->shader, surf->fogIndex, dlightBits, pshadowBits, surf->cubemapIndex );
}