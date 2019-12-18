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

/* Variables and functions */
 int /*<<< orphan*/  MatchToken (char*) ; 
 int /*<<< orphan*/  Parse2DMatrix (int,int,int /*<<< orphan*/ *) ; 

void Parse3DMatrix( int z, int y, int x, vec_t *m ) {
	int i;

	MatchToken( "(" );

	for ( i = 0 ; i < z ; i++ ) {
		Parse2DMatrix( y, x, m + i * x * y );
	}

	MatchToken( ")" );
}