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
typedef  int /*<<< orphan*/  tf_triangle ;

/* Variables and functions */
 int BigLong (int) ; 

__attribute__((used)) static void ByteSwapTri( tf_triangle *tri ){
	int i;

	for ( i = 0 ; i < sizeof( tf_triangle ) / 4 ; i++ )
	{
		( (int *)tri )[i] = BigLong( ( (int *)tri )[i] );
	}
}