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
typedef  int /*<<< orphan*/ * m4x4_t ;
typedef  int /*<<< orphan*/ * m3x3_t ;

/* Variables and functions */

void m4_submat( m4x4_t mr, m3x3_t mb, int i, int j ){
	int ti, tj, idst, jdst;

	idst = 0;
	for ( ti = 0; ti < 4; ti++ )
	{
		if ( ti == i ) {
			continue;
		}
		if ( ti < i ) {
			idst = ti;
		}
		else
		{
			idst = ti - 1;
		}

		for ( tj = 0; tj < 4; tj++ )
		{
			if ( tj == j ) {
				continue;
			}
			if ( tj < j ) {
				jdst = tj;
			}
			else
			{
				jdst = tj - 1;
			}

			mb[idst * 3 + jdst] = mr[ti * 4 + tj ];
		}
	}
}