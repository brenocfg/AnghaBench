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
typedef  int vec_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void Write1DMatrix( FILE *f, int x, vec_t *m ) {
	int i;

	fprintf( f, "( " );
	for ( i = 0 ; i < x ; i++ ) {
		if ( m[i] == (int)m[i] ) {
			fprintf( f, "%i ", (int)m[i] );
		}
		else {
			fprintf( f, "%f ", m[i] );
		}
	}
	fprintf( f, ")" );
}