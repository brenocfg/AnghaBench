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
struct TYPE_3__ {int /*<<< orphan*/  shader; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_4__ {TYPE_1__* si; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* surfaceInfos ; 

__attribute__((used)) static int CompareLightSurface( const void *a, const void *b ){
	shaderInfo_t    *asi, *bsi;


	/* get shaders */
	asi = surfaceInfos[ *( (int*) a ) ].si;
	bsi = surfaceInfos[ *( (int*) b ) ].si;

	/* dummy check */
	if ( asi == NULL ) {
		return -1;
	}
	if ( bsi == NULL ) {
		return 1;
	}

	/* compare shader names */
	return strcmp( asi->shader, bsi->shader );
}