#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float f; int /*<<< orphan*/ * c; } ;
typedef  TYPE_1__ floatSwapUnion ;

/* Variables and functions */

float DDSBigFloat( float src ){
	floatSwapUnion in,out;
	in.f = src;
	out.c[ 0 ] = in.c[ 3 ];
	out.c[ 1 ] = in.c[ 2 ];
	out.c[ 2 ] = in.c[ 1 ];
	out.c[ 3 ] = in.c[ 0 ];
	return out.f;
}