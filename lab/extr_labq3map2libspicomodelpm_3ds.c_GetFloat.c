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
struct TYPE_3__ {scalar_t__ cofs; scalar_t__ maxofs; scalar_t__ bufptr; } ;
typedef  TYPE_1__ T3dsLoaderPers ;

/* Variables and functions */
 float _pico_little_float (float) ; 

__attribute__((used)) static float GetFloat( T3dsLoaderPers *pers ){
	float *value;

	/* sanity check */
	if ( pers->cofs > pers->maxofs ) {
		return 0;
	}

	/* get and return value */
	value = (float *)( pers->bufptr + pers->cofs );
	pers->cofs += 4;
	return _pico_little_float( *value );
}