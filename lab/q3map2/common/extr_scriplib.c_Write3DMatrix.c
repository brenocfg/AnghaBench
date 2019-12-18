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
 int /*<<< orphan*/  Write2DMatrix (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void Write3DMatrix( FILE *f, int z, int y, int x, vec_t *m ) {
	int i;

	fprintf( f, "(\n" );
	for ( i = 0 ; i < z ; i++ ) {
		Write2DMatrix( f, y, x, m + i * ( x * y ) );
	}
	fprintf( f, ")\n" );
}