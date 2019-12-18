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
typedef  float* picoVec2_t ;
typedef  int /*<<< orphan*/  picoParser_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_copy_vec2 (float*,float*) ; 
 char* _pico_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atof (char*) ; 

int _pico_parse_vec2_def( picoParser_t *p, picoVec2_t out, picoVec2_t def ){
	char *token;
	int i;

	/* sanity checks */
	if ( p == NULL || out == NULL ) {
		return 0;
	}

	/* assign default vector value */
	_pico_copy_vec2( def,out );

	/* parse two vector components */
	for ( i = 0; i < 2; i++ )
	{
		token = _pico_parse( p,0 );
		if ( token == NULL ) {
			_pico_copy_vec2( def,out );
			return 0;
		}
		out[ i ] = (float) atof( token );
	}
	/* success */
	return 1;
}