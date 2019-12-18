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
typedef  size_t uint8_t ;
struct algo_needs {int* needs; } ;

/* Variables and functions */

void algo_needs_set_bogus(struct algo_needs* n, uint8_t algo)
{
	if(n->needs[algo]) n->needs[algo] = 2; /* need it, but bogus */
}