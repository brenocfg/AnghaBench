#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FillRect (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCREEN_HEIGHT ; 
 int /*<<< orphan*/  SCREEN_WIDTH ; 
 int /*<<< orphan*/  dmlab_get_filled_rectangle (int,int*,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int dmlab_make_filled_rectangles (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_DrawScriptFilledRectangles( void ) {
	int i, x, y, width, height;
	vec4_t rgba;
	int c = dmlab_make_filled_rectangles( SCREEN_WIDTH, SCREEN_HEIGHT );
	for (i = 0; i < c; ++i) {
		dmlab_get_filled_rectangle( i, &x, &y, &width, &height, rgba );
		CG_FillRect( x, y, width, height, rgba );
	}
}