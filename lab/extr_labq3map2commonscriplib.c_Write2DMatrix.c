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
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Write1DMatrix (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void Write2DMatrix( FILE *f, int y, int x, vec_t *m ) {
	int i;

	fprintf( f, "( " );
	for ( i = 0 ; i < y ; i++ ) {
		Write1DMatrix( f, x, m + i * x );
		fprintf( f, " " );
	}
	fprintf( f, ")\n" );
}