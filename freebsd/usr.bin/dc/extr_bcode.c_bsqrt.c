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
typedef  int u_int ;
struct number {int scale; int /*<<< orphan*/ * number; } ;
struct TYPE_2__ {int /*<<< orphan*/  scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ bmachine ; 
 struct number* bmalloc (int) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 scalar_t__ bsqrt_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,int) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
bsqrt(void)
{
	struct number *n, *r;
	BIGNUM *x, *y;
	BN_CTX *ctx;
	u_int onecount, scale;

	onecount = 0;
	n = pop_number();
	if (n == NULL)
		return;
	if (BN_is_zero(n->number)) {
		r = new_number();
		push_number(r);
	} else if (BN_is_negative(n->number))
		warnx("square root of negative number");
	else {
		scale = max(bmachine.scale, n->scale);
		normalize(n, 2*scale);
		x = BN_dup(n->number);
		bn_checkp(x);
		bn_check(BN_rshift(x, x, BN_num_bits(x)/2));
		y = BN_new();
		bn_checkp(y);
		ctx = BN_CTX_new();
		bn_checkp(ctx);
		for (;;) {
			bn_checkp(BN_copy(y, x));
			bn_check(BN_div(x, NULL, n->number, x, ctx));
			bn_check(BN_add(x, x, y));
			bn_check(BN_rshift1(x, x));
			if (bsqrt_stop(x, y, &onecount))
				break;
		}
		r = bmalloc(sizeof(*r));
		r->scale = scale;
		r->number = y;
		BN_free(x);
		BN_CTX_free(ctx);
		push_number(r);
	}

	free_number(n);
}