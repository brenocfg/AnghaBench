#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ shape; float time; float* param; float value; } ;
typedef  TYPE_1__ lwKey ;

/* Variables and functions */
 scalar_t__ ID_BEZ2 ; 
 float bez2_time (float,float,float,float,float,float*,float*) ; 
 float bezier (float,float,float,float,float) ; 

__attribute__((used)) static float bez2( lwKey *key0, lwKey *key1, float time ){
	float x, y, t, t0 = 0.0f, t1 = 1.0f;

	if ( key0->shape == ID_BEZ2 ) {
		x = key0->time + key0->param[ 2 ];
	}
	else{
		x = key0->time + ( key1->time - key0->time ) / 3.0f;
	}

	t = bez2_time( key0->time, x, key1->time + key1->param[ 0 ], key1->time,
				   time, &t0, &t1 );

	if ( key0->shape == ID_BEZ2 ) {
		y = key0->value + key0->param[ 3 ];
	}
	else{
		y = key0->value + key0->param[ 1 ] / 3.0f;
	}

	return bezier( key0->value, y, key1->param[ 1 ] + key1->value, key1->value, t );
}