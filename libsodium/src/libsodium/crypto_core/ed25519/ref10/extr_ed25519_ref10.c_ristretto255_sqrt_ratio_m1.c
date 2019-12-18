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
typedef  int /*<<< orphan*/  const fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_abs (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 
 int fe25519_iszero (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_pow22523 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_sq (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const sqrtm1 ; 

__attribute__((used)) static int
ristretto255_sqrt_ratio_m1(fe25519 x, const fe25519 u, const fe25519 v)
{
    fe25519 v3;
    fe25519 vxx;
    fe25519 m_root_check, p_root_check, f_root_check;
    fe25519 x_sqrtm1;
    int     has_m_root, has_p_root, has_f_root;

    fe25519_sq(v3, v);
    fe25519_mul(v3, v3, v); /* v3 = v^3 */
    fe25519_sq(x, v3);
    fe25519_mul(x, x, v);
    fe25519_mul(x, x, u); /* x = uv^7 */

    fe25519_pow22523(x, x); /* x = (uv^7)^((q-5)/8) */
    fe25519_mul(x, x, v3);
    fe25519_mul(x, x, u); /* x = uv^3(uv^7)^((q-5)/8) */

    fe25519_sq(vxx, x);
    fe25519_mul(vxx, vxx, v); /* vx^2 */
    fe25519_sub(m_root_check, vxx, u); /* vx^2-u */
    fe25519_add(p_root_check, vxx, u); /* vx^2+u */
    fe25519_mul(f_root_check, u, sqrtm1); /* u*sqrt(-1) */
    fe25519_add(f_root_check, vxx, f_root_check); /* vx^2+u*sqrt(-1) */
    has_m_root = fe25519_iszero(m_root_check);
    has_p_root = fe25519_iszero(p_root_check);
    has_f_root = fe25519_iszero(f_root_check);
    fe25519_mul(x_sqrtm1, x, sqrtm1); /* x*sqrt(-1) */

    fe25519_cmov(x, x_sqrtm1, has_p_root | has_f_root);
    fe25519_abs(x, x);

    return has_m_root | has_p_root;
}