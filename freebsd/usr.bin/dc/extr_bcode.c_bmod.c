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
typedef  int /*<<< orphan*/  u_int ;
struct number {int /*<<< orphan*/  number; int /*<<< orphan*/  scale; } ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct number* new_number () ; 
 int /*<<< orphan*/  normalize (struct number*,int /*<<< orphan*/ ) ; 
 struct number* pop_number () ; 
 int /*<<< orphan*/  push_number (struct number*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
bmod(void)
{
	struct number *a, *b, *r;
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

	r = new_number();
	scale = max(a->scale, b->scale);
	r->scale = scale;

	if (BN_is_zero(a->number))
		warnx("remainder by zero");
	else {
		normalize(a, scale);
		normalize(b, scale);

		ctx = BN_CTX_new();
		bn_checkp(ctx);
		bn_check(BN_mod(r->number, b->number, a->number, ctx));
		BN_CTX_free(ctx);
	}
	push_number(r);
	free_number(a);
	free_number(b);
}