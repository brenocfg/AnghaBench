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
struct source {TYPE_1__* vtable; } ;
struct number {int scale; int /*<<< orphan*/ * number; } ;
struct TYPE_2__ {int (* readchar ) (struct source*) ;int /*<<< orphan*/  (* unreadchar ) (struct source*) ;} ;
typedef  int BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_mul_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int EOF ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 struct number* div_number (struct number*,struct number*,int) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int /*<<< orphan*/  negate (struct number*) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 
 int stub1 (struct source*) ; 
 int /*<<< orphan*/  stub2 (struct source*) ; 

struct number *
readnumber(struct source *src, u_int base, u_int bscale)
{
	struct number *n;
	BN_ULONG v;
	int ch;
	u_int iscale = 0;
	bool dot = false, sign = false;

	n = new_number();
	bn_check(BN_zero(n->number));

	while ((ch = (*src->vtable->readchar)(src)) != EOF) {

		if ('0' <= ch && ch <= '9')
			v = ch - '0';
		else if ('A' <= ch && ch <= 'F')
			v = ch - 'A' + 10;
		else if (ch == '_') {
			sign = true;
			continue;
		} else if (ch == '.') {
			if (dot)
				break;
			dot = true;
			continue;
		} else {
			(*src->vtable->unreadchar)(src);
			break;
		}
		if (dot)
			iscale++;

		bn_check(BN_mul_word(n->number, base));
		bn_check(BN_add_word(n->number, v));
	}
	if (base == 10) {
		n->scale = iscale;
	} else {
		/* At this point, the desired result is n->number / base^iscale*/
		struct number *quotient, *divisor, *_n;
		BIGNUM *base_n, *exponent;
		BN_CTX *ctx;

		ctx = BN_CTX_new();
		base_n = BN_new();
		exponent = BN_new();
		divisor = new_number();
		bn_check(BN_zero(base_n));
		bn_check(BN_zero(exponent));

		bn_check(BN_add_word(base_n, base));
		bn_check(BN_add_word(exponent, iscale));
		bn_check(BN_exp(divisor->number, base_n, exponent, ctx));
		divisor->scale = 0;
		quotient = div_number(n, divisor, bscale);
		_n = n;
		n = quotient;

		/* 
		 * Trim off trailing zeros to yield the smallest scale without
		 * loss of accuracy
		 */
		while ( n->scale > 0 &&
			BN_mod_word(n->number, 10) == 0) {
			normalize(n, n->scale - 1);
		}

		free_number(_n);
		free_number(divisor);
		BN_CTX_free(ctx);
		BN_free(base_n);
		BN_free(exponent);
	}
	if (sign)
		negate(n);
	return (n);
}