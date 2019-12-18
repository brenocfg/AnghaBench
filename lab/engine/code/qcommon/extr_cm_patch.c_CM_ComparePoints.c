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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 float POINT_EPSILON ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean CM_ComparePoints( float *a, float *b ) {
	float		d;

	d = a[0] - b[0];
	if ( d < -POINT_EPSILON || d > POINT_EPSILON ) {
		return qfalse;
	}
	d = a[1] - b[1];
	if ( d < -POINT_EPSILON || d > POINT_EPSILON ) {
		return qfalse;
	}
	d = a[2] - b[2];
	if ( d < -POINT_EPSILON || d > POINT_EPSILON ) {
		return qfalse;
	}
	return qtrue;
}