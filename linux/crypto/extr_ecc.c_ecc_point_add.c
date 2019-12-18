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
struct ecc_point {int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; } ;
struct TYPE_2__ {unsigned int ndigits; } ;
struct ecc_curve {int /*<<< orphan*/  p; TYPE_1__ g; } ;

/* Variables and functions */
 int ECC_MAX_DIGITS ; 
 int /*<<< orphan*/  apply_z (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_inv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_mod_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vli_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  xycz_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ecc_point_add(const struct ecc_point *result,
		   const struct ecc_point *p, const struct ecc_point *q,
		   const struct ecc_curve *curve)
{
	u64 z[ECC_MAX_DIGITS];
	u64 px[ECC_MAX_DIGITS];
	u64 py[ECC_MAX_DIGITS];
	unsigned int ndigits = curve->g.ndigits;

	vli_set(result->x, q->x, ndigits);
	vli_set(result->y, q->y, ndigits);
	vli_mod_sub(z, result->x, p->x, curve->p, ndigits);
	vli_set(px, p->x, ndigits);
	vli_set(py, p->y, ndigits);
	xycz_add(px, py, result->x, result->y, curve->p, ndigits);
	vli_mod_inv(z, z, curve->p, ndigits);
	apply_z(result->x, result->y, z, curve->p, ndigits);
}