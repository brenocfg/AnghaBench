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
typedef  float* m4x4_t ;
typedef  int /*<<< orphan*/  m3x3_t ;

/* Variables and functions */
 float m3_det (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m4_submat (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

float m4_det( m4x4_t mr ){
	float det, result = 0, i = 1;
	m3x3_t msub3;
	int n;

	for ( n = 0; n < 4; n++, i *= -1 )
	{
		m4_submat( mr, msub3, 0, n );

		det     = m3_det( msub3 );
		result += mr[n] * det * i;
	}

	return result;
}