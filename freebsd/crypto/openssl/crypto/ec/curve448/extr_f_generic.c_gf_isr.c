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
typedef  int /*<<< orphan*/  mask_t ;
typedef  int /*<<< orphan*/  const gf ;

/* Variables and functions */
 int /*<<< orphan*/  ONE ; 
 int /*<<< orphan*/  gf_copy (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_eq (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_sqr (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_sqrn (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 

mask_t gf_isr(gf a, const gf x)
{
    gf L0, L1, L2;

    gf_sqr(L1, x);
    gf_mul(L2, x, L1);
    gf_sqr(L1, L2);
    gf_mul(L2, x, L1);
    gf_sqrn(L1, L2, 3);
    gf_mul(L0, L2, L1);
    gf_sqrn(L1, L0, 3);
    gf_mul(L0, L2, L1);
    gf_sqrn(L2, L0, 9);
    gf_mul(L1, L0, L2);
    gf_sqr(L0, L1);
    gf_mul(L2, x, L0);
    gf_sqrn(L0, L2, 18);
    gf_mul(L2, L1, L0);
    gf_sqrn(L0, L2, 37);
    gf_mul(L1, L2, L0);
    gf_sqrn(L0, L1, 37);
    gf_mul(L1, L2, L0);
    gf_sqrn(L0, L1, 111);
    gf_mul(L2, L1, L0);
    gf_sqr(L0, L2);
    gf_mul(L1, x, L0);
    gf_sqrn(L0, L1, 223);
    gf_mul(L1, L2, L0);
    gf_sqr(L2, L1);
    gf_mul(L0, L2, x);
    gf_copy(a, L1);
    return gf_eq(L0, ONE);
}