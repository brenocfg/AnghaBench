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
typedef  unsigned long long uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {unsigned long long state; int inc; } ;

/* Variables and functions */
 TYPE_1__ rng ; 

__attribute__((used)) static uint32_t
pcg32_random (void)
{
	uint64_t oldstate = rng.state;

	rng.state = oldstate * 6364136223846793005ULL + (rng.inc | 1);
	uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	uint32_t rot = oldstate >> 59u;
	return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}