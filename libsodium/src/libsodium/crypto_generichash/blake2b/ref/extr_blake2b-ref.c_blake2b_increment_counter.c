#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint128_t ;
struct TYPE_3__ {int* t; } ;
typedef  TYPE_1__ blake2b_state ;

/* Variables and functions */

__attribute__((used)) static inline int
blake2b_increment_counter(blake2b_state *S, const uint64_t inc)
{
#ifdef HAVE_TI_MODE
    uint128_t t = ((uint128_t) S->t[1] << 64) | S->t[0];
    t += inc;
    S->t[0] = (uint64_t)(t >> 0);
    S->t[1] = (uint64_t)(t >> 64);
#else
    S->t[0] += inc;
    S->t[1] += (S->t[0] < inc);
#endif
    return 0;
}