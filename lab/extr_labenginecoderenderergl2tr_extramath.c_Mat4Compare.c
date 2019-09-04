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
typedef  int qboolean ;
typedef  scalar_t__* mat4_t ;

/* Variables and functions */

qboolean Mat4Compare( const mat4_t a, const mat4_t b )
{
	return !(a[ 0] != b[ 0] || a[ 4] != b[ 4] || a[ 8] != b[ 8] || a[12] != b[12] ||
             a[ 1] != b[ 1] || a[ 5] != b[ 5] || a[ 9] != b[ 9] || a[13] != b[13] ||
		     a[ 2] != b[ 2] || a[ 6] != b[ 6] || a[10] != b[10] || a[14] != b[14] ||
		     a[ 3] != b[ 3] || a[ 7] != b[ 7] || a[11] != b[11] || a[15] != b[15]);
}