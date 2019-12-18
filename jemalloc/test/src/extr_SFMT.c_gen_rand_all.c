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
typedef  int /*<<< orphan*/  w128_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sfmt; } ;
typedef  TYPE_1__ sfmt_t ;

/* Variables and functions */
 int N ; 
 int POS1 ; 
 int /*<<< orphan*/  do_recursion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gen_rand_all(sfmt_t *ctx) {
    int i;
    w128_t *r1, *r2;

    r1 = &ctx->sfmt[N - 2];
    r2 = &ctx->sfmt[N - 1];
    for (i = 0; i < N - POS1; i++) {
	do_recursion(&ctx->sfmt[i], &ctx->sfmt[i], &ctx->sfmt[i + POS1], r1,
	  r2);
	r1 = r2;
	r2 = &ctx->sfmt[i];
    }
    for (; i < N; i++) {
	do_recursion(&ctx->sfmt[i], &ctx->sfmt[i], &ctx->sfmt[i + POS1 - N], r1,
	  r2);
	r1 = r2;
	r2 = &ctx->sfmt[i];
    }
}