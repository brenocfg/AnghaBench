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
typedef  scalar_t__* vec5_t ;

/* Variables and functions */

void _Vector5Add( vec5_t va, vec5_t vb, vec5_t out ){
	out[0] = va[0] + vb[0];
	out[1] = va[1] + vb[1];
	out[2] = va[2] + vb[2];
	out[3] = va[3] + vb[3];
	out[4] = va[4] + vb[4];
}