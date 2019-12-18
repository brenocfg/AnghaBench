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
struct TYPE_3__ {int time; } ;
struct TYPE_4__ {scalar_t__ isHyperspace; TYPE_1__ refdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 TYPE_2__ backEnd ; 
 int /*<<< orphan*/  qglClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClearColor (float,float,float,float) ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static void RB_Hyperspace( void ) {
	float		c;

	if ( !backEnd.isHyperspace ) {
		// do initialization shit
	}

	c = ( backEnd.refdef.time & 255 ) / 255.0f;
	qglClearColor( c, c, c, 1 );
	qglClear( GL_COLOR_BUFFER_BIT );
	qglClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	backEnd.isHyperspace = qtrue;
}