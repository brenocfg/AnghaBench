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
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 float fabs (scalar_t__) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean VectorCompareExt( vec3_t n1, vec3_t n2, float epsilon ){
	int i;


	/* test */
	for ( i = 0; i < 3; i++ )
		if ( fabs( n1[ i ] - n2[ i ] ) > epsilon ) {
			return qfalse;
		}
	return qtrue;
}