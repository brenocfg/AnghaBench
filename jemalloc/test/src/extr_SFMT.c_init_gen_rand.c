#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w128_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int idx; int initialized; TYPE_1__* sfmt; } ;
typedef  TYPE_2__ sfmt_t ;
struct TYPE_5__ {int* u; } ;

/* Variables and functions */
 int N32 ; 
 size_t idxof (int) ; 
 int /*<<< orphan*/  period_certification (TYPE_2__*) ; 
 scalar_t__ posix_memalign (void**,int,int) ; 

sfmt_t *init_gen_rand(uint32_t seed) {
    void *p;
    sfmt_t *ctx;
    int i;
    uint32_t *psfmt32;

    if (posix_memalign(&p, sizeof(w128_t), sizeof(sfmt_t)) != 0) {
	return NULL;
    }
    ctx = (sfmt_t *)p;
    psfmt32 = &ctx->sfmt[0].u[0];

    psfmt32[idxof(0)] = seed;
    for (i = 1; i < N32; i++) {
	psfmt32[idxof(i)] = 1812433253UL * (psfmt32[idxof(i - 1)]
					    ^ (psfmt32[idxof(i - 1)] >> 30))
	    + i;
    }
    ctx->idx = N32;
    period_certification(ctx);
    ctx->initialized = 1;

    return ctx;
}