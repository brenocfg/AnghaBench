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
struct TYPE_3__ {int height; float*** points; int width; int /*<<< orphan*/  wrapWidth; } ;
typedef  TYPE_1__ cGrid_t ;

/* Variables and functions */
 float WRAP_POINT_EPSILON ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void CM_SetGridWrapWidth( cGrid_t *grid ) {
	int		i, j;
	float	d;

	for ( i = 0 ; i < grid->height ; i++ ) {
		for ( j = 0 ; j < 3 ; j++ ) {
			d = grid->points[0][i][j] - grid->points[grid->width-1][i][j];
			if ( d < -WRAP_POINT_EPSILON || d > WRAP_POINT_EPSILON ) {
				break;
			}
		}
		if ( j != 3 ) {
			break;
		}
	}
	if ( i == grid->height ) {
		grid->wrapWidth = qtrue;
	} else {
		grid->wrapWidth = qfalse;
	}
}