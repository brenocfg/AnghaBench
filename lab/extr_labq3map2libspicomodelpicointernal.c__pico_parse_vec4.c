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
typedef  float* picoVec4_t ;
typedef  int /*<<< orphan*/  picoParser_t ;

/* Variables and functions */
 char* _pico_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_zero_vec4 (float*) ; 
 scalar_t__ atof (char*) ; 

int _pico_parse_vec4( picoParser_t *p, picoVec4_t out ){
	char *token;
	int i;

	/* sanity checks */
	if ( p == NULL || out == NULL ) {
		return 0;
	}

	/* zero out outination vector */
	_pico_zero_vec4( out );

	/* parse four vector components */
	for ( i = 0; i < 4; i++ )
	{
		token = _pico_parse( p,0 );
		if ( token == NULL ) {
			_pico_zero_vec4( out );
			return 0;
		}
		out[ i ] = (float) atof( token );
	}
	/* success */
	return 1;
}