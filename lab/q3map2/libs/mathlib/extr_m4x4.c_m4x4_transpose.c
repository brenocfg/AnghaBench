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

/* Variables and functions */

void m4x4_transpose( m4x4_t matrix ){
	int i, j;
	float temp, *p1, *p2;

	for ( i = 1; i < 4; i++ ) {
		for ( j = 0; j < i; j++ ) {
			p1 = matrix + ( j * 4 + i );
			p2 = matrix + ( i * 4 + j );
			temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
	}
}