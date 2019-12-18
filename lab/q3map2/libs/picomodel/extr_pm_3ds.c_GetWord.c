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
 int _pico_little_short (unsigned short) ; 

__attribute__((used)) static int GetWord( T3dsLoaderPers *pers ){
	unsigned short *value;

	/* sanity check */
	if ( pers->cofs > pers->maxofs ) {
		return 0;
	}

	/* get and return value */
	value = (unsigned short *)( pers->bufptr + pers->cofs );
	pers->cofs += 2;
	return _pico_little_short( *value );
}