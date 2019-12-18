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
typedef  int /*<<< orphan*/  picoParser_t ;

/* Variables and functions */
 char* _pico_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 

int _pico_parse_int_def( picoParser_t *p, int *out, int def ){
	char *token;

	/* sanity checks */
	if ( p == NULL || out == NULL ) {
		return 0;
	}

	/* get token and turn it into an integer */
	*out = def;
	token = _pico_parse( p,0 );
	if ( token == NULL ) {
		return 0;
	}
	*out = atoi( token );

	/* success */
	return 1;
}