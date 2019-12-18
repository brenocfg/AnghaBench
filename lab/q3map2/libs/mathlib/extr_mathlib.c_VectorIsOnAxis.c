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
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean VectorIsOnAxis( vec3_t v ){
	int i, zeroComponentCount;

	zeroComponentCount = 0;
	for ( i = 0; i < 3; i++ )
	{
		if ( v[i] == 0.0 ) {
			zeroComponentCount++;
		}
	}

	if ( zeroComponentCount > 1 ) {
		// The zero vector will be on axis.
		return qtrue;
	}

	return qfalse;
}