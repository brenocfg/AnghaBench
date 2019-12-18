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
typedef  scalar_t__ u_int ;
struct number {scalar_t__ scale; int /*<<< orphan*/  number; } ;
struct TYPE_2__ {scalar_t__ scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 

void
bmul_number(struct number *r, struct number *a, struct number *b, u_int scale)
{
	BN_CTX *ctx;

	/* Create copies of the scales, since r might be equal to a or b */
	u_int ascale = a->scale;
	u_int bscale = b->scale;
	u_int rscale = ascale + bscale;

	ctx = BN_CTX_new();
	bn_checkp(ctx);
	bn_check(BN_mul(r->number, a->number, b->number, ctx));
	BN_CTX_free(ctx);

	r->scale = rscale;
	if (rscale > bmachine.scale && rscale > ascale && rscale > bscale)
		normalize(r, max(scale, max(ascale, bscale)));
}