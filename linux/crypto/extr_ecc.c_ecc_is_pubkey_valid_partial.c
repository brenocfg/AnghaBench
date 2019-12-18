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
typedef  int /*<<< orphan*/  u64 ;
struct ecc_point {scalar_t__ ndigits; int /*<<< orphan*/ * x; int /*<<< orphan*/ * y; } ;
struct TYPE_2__ {scalar_t__ ndigits; } ;
struct ecc_curve {int /*<<< orphan*/ * p; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; TYPE_1__ g; } ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ecc_point_is_zero (struct ecc_point*) ; 
 scalar_t__ vli_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vli_mod_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vli_mod_mult_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vli_mod_square_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int ecc_is_pubkey_valid_partial(const struct ecc_curve *curve,
				struct ecc_point *pk)
{
	u64 yy[ECC_MAX_DIGITS], xxx[ECC_MAX_DIGITS], w[ECC_MAX_DIGITS];

	if (WARN_ON(pk->ndigits != curve->g.ndigits))
		return -EINVAL;

	/* Check 1: Verify key is not the zero point. */
	if (ecc_point_is_zero(pk))
		return -EINVAL;

	/* Check 2: Verify key is in the range [1, p-1]. */
	if (vli_cmp(curve->p, pk->x, pk->ndigits) != 1)
		return -EINVAL;
	if (vli_cmp(curve->p, pk->y, pk->ndigits) != 1)
		return -EINVAL;

	/* Check 3: Verify that y^2 == (x^3 + a·x + b) mod p */
	vli_mod_square_fast(yy, pk->y, curve->p, pk->ndigits); /* y^2 */
	vli_mod_square_fast(xxx, pk->x, curve->p, pk->ndigits); /* x^2 */
	vli_mod_mult_fast(xxx, xxx, pk->x, curve->p, pk->ndigits); /* x^3 */
	vli_mod_mult_fast(w, curve->a, pk->x, curve->p, pk->ndigits); /* a·x */
	vli_mod_add(w, w, curve->b, curve->p, pk->ndigits); /* a·x + b */
	vli_mod_add(w, w, xxx, curve->p, pk->ndigits); /* x^3 + a·x + b */
	if (vli_cmp(yy, w, pk->ndigits) != 0) /* Equation */
		return -EINVAL;

	return 0;
}