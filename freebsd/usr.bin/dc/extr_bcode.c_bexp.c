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
typedef  scalar_t__ u_long ;
typedef  int u_int ;
struct number {scalar_t__ scale; int /*<<< orphan*/ * number; } ;
struct TYPE_2__ {int scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_bit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ ULONG_MAX ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bmul_number (struct number*,struct number*,struct number*,int) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 struct number* dup_number (struct number*) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int max (scalar_t__,int) ; 
 int /*<<< orphan*/  negate (struct number*) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,int) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  scale_number (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  split_number (struct number*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
bexp(void)
{
	struct number	*a, *p;
	struct number	*r;
	bool		neg;
	u_int		rscale;

	p = pop_number();
	if (p == NULL)
		return;
	a = pop_number();
	if (a == NULL) {
		push_number(p);
		return;
	}

	if (p->scale != 0) {
		BIGNUM *i, *f;
		i = BN_new();
		bn_checkp(i);
		f = BN_new();
		bn_checkp(f);
		split_number(p, i, f);
		if (!BN_is_zero(f))
			warnx("Runtime warning: non-zero fractional part in exponent");
		BN_free(i);
		BN_free(f);
	}

	normalize(p, 0);

	neg = false;
	if (BN_is_negative(p->number)) {
		neg = true;
		negate(p);
		rscale = bmachine.scale;
	} else {
		/* Posix bc says min(a.scale * b, max(a.scale, scale) */
		u_long b;
		u_int m;

		b = BN_get_word(p->number);
		m = max(a->scale, bmachine.scale);
		rscale = a->scale * (u_int)b;
		if (rscale > m || (a->scale > 0 && (b == ULONG_MAX ||
		    b > UINT_MAX)))
			rscale = m;
	}

	if (BN_is_zero(p->number)) {
		r = new_number();
		bn_check(BN_one(r->number));
		normalize(r, rscale);
	} else {
		u_int ascale, mscale;

		ascale = a->scale;
		while (!BN_is_bit_set(p->number, 0)) {
			ascale *= 2;
			bmul_number(a, a, a, ascale);
			bn_check(BN_rshift1(p->number, p->number));
		}

		r = dup_number(a);
		bn_check(BN_rshift1(p->number, p->number));

		mscale = ascale;
		while (!BN_is_zero(p->number)) {
			ascale *= 2;
			bmul_number(a, a, a, ascale);
			if (BN_is_bit_set(p->number, 0)) {
				mscale += ascale;
				bmul_number(r, r, a, mscale);
			}
			bn_check(BN_rshift1(p->number, p->number));
		}

		if (neg) {
			BN_CTX *ctx;
			BIGNUM *one;

			one = BN_new();
			bn_checkp(one);
			bn_check(BN_one(one));
			ctx = BN_CTX_new();
			bn_checkp(ctx);
			scale_number(one, r->scale + rscale);

			if (BN_is_zero(r->number))
				warnx("divide by zero");
			else
				bn_check(BN_div(r->number, NULL, one,
				    r->number, ctx));
			BN_free(one);
			BN_CTX_free(ctx);
			r->scale = rscale;
		} else
			normalize(r, rscale);
	}
	push_number(r);
	free_number(a);
	free_number(p);
}