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
struct TYPE_3__ {unsigned long* mt; int mti; } ;
typedef  TYPE_1__ mt_state ;

/* Variables and functions */
 int N ; 

void mrb_random_init_genrand(mt_state *t, unsigned long s)
{
    t->mt[0]= s & 0xffffffffUL;
    for (t->mti=1; t->mti<N; t->mti++) {
        t->mt[t->mti] = (1812433253UL * (t->mt[t->mti-1] ^ (t->mt[t->mti-1] >> 30)) + t->mti);
        t->mt[t->mti] &= 0xffffffffUL;
    }
}