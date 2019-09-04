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
typedef  scalar_t__* vec3_t ;

/* Variables and functions */

__attribute__((used)) static int CM_SignbitsForNormal( vec3_t normal ) {
	int	bits, j;

	bits = 0;
	for (j=0 ; j<3 ; j++) {
		if ( normal[j] < 0 ) {
			bits |= 1<<j;
		}
	}
	return bits;
}