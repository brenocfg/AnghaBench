#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int ;
struct number {int /*<<< orphan*/  number; scalar_t__ scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*) ; 

struct number *
div_number(struct number *dividend, struct number *divisor, u_int bscale)
{
	struct number *quotient;
	BN_CTX *ctx;
	u_int scale;

	quotient = new_number();
	quotient->scale = bscale;
	scale = max(divisor->scale, dividend->scale);

	if (BN_is_zero(divisor->number))
		warnx("divide by zero");
	else {
		normalize(divisor, scale);
		normalize(dividend, scale + quotient->scale);

		ctx = BN_CTX_new();
		bn_checkp(ctx);
		bn_check(BN_div(quotient->number, NULL, dividend->number,
				divisor->number, ctx));
		BN_CTX_free(ctx);
	}
	return (quotient);
}