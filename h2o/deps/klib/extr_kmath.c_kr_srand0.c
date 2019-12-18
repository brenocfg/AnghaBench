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
typedef  unsigned long long krint64_t ;
struct TYPE_3__ {unsigned long long* mt; int mti; } ;
typedef  TYPE_1__ krand_t ;

/* Variables and functions */
 int KR_NN ; 

__attribute__((used)) static void kr_srand0(krint64_t seed, krand_t *kr)
{
	kr->mt[0] = seed;
	for (kr->mti = 1; kr->mti < KR_NN; ++kr->mti) 
		kr->mt[kr->mti] = 6364136223846793005ULL * (kr->mt[kr->mti - 1] ^ (kr->mt[kr->mti - 1] >> 62)) + kr->mti;
}