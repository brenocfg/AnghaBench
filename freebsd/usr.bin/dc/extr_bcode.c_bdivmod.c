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
struct number {int /*<<< orphan*/  number; scalar_t__ scale; } ;
struct TYPE_2__ {scalar_t__ scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 struct number* div_number (struct number*,struct number*,scalar_t__) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
bdivmod(void)
{
	struct number *a, *b, *frac, *quotient, *rdiv, *remainder;
	BN_CTX *ctx;
	u_int scale;

	a = pop_number();
	if (a == NULL)
		return;
	b = pop_number();
	if (b == NULL) {
		push_number(a);
		return;
	}

	rdiv = new_number();
	quotient = new_number();
	remainder = new_number();
	scale = max(a->scale, b->scale);
	rdiv->scale = 0;
	remainder->scale = scale;
	quotient->scale = bmachine.scale;
	scale = max(a->scale, b->scale);

	if (BN_is_zero(a->number))
		warnx("divide by zero");
	else {
		normalize(a, scale);
		normalize(b, scale);

		ctx = BN_CTX_new();
		bn_checkp(ctx);
		/*
		 * Unlike other languages' divmod operations, dc is specified
		 * to return the remainder and the full quotient, rather than
		 * the remainder and the floored quotient.  bn(3) has no
		 * function to calculate both.  So we'll use BN_div to get the
		 * remainder and floored quotient, then calculate the full
		 * quotient from those.
		 *
		 * quotient = rdiv + remainder / divisor
		 */
		bn_check(BN_div(rdiv->number, remainder->number,
		    b->number, a->number, ctx));
		frac = div_number(remainder, a, bmachine.scale);
		normalize(rdiv, bmachine.scale);
		normalize(remainder, scale);
		bn_check(BN_add(quotient->number, rdiv->number, frac->number));
		free_number(frac);
		BN_CTX_free(ctx);
	}
	push_number(quotient);
	push_number(remainder);
	free_number(rdiv);
	free_number(a);
	free_number(b);
}