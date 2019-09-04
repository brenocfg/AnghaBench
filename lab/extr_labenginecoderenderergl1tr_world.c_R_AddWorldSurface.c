#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ viewCount; int /*<<< orphan*/  fogIndex; int /*<<< orphan*/  shader; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ msurface_t ;
struct TYPE_6__ {scalar_t__ viewCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_AddDrawSurf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ R_CullSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R_DlightSurface (TYPE_1__*,int) ; 
 TYPE_2__ tr ; 

__attribute__((used)) static void R_AddWorldSurface( msurface_t *surf, int dlightBits ) {
	if ( surf->viewCount == tr.viewCount ) {
		return;		// already in this view
	}

	surf->viewCount = tr.viewCount;
	// FIXME: bmodel fog?

	// try to cull before dlighting or adding
	if ( R_CullSurface( surf->data, surf->shader ) ) {
		return;
	}

	// check for dlighting
	if ( dlightBits ) {
		dlightBits = R_DlightSurface( surf, dlightBits );
		dlightBits = ( dlightBits != 0 );
	}

	R_AddDrawSurf( surf->data, surf->shader, surf->fogIndex, dlightBits );
}