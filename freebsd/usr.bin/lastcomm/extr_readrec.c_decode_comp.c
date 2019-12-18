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
typedef  int comp_t ;

/* Variables and functions */
 double AHZV1 ; 

__attribute__((used)) static float
decode_comp(comp_t v)
{
	int result, exp;

	result = v & 017777;
	for (exp = v >> 13; exp; exp--)
		result <<= 3;
	return ((double)result / AHZV1);
}