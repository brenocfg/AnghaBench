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
typedef  int /*<<< orphan*/  widefelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_128_64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_sum (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  widefelem_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widefelem_scalar (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
point_double(felem x_out, felem y_out, felem z_out,
             const felem x_in, const felem y_in, const felem z_in)
{
    widefelem tmp, tmp2;
    felem delta, gamma, beta, alpha, ftmp, ftmp2;

    felem_assign(ftmp, x_in);
    felem_assign(ftmp2, x_in);

    /* delta = z^2 */
    felem_square(tmp, z_in);
    felem_reduce(delta, tmp);

    /* gamma = y^2 */
    felem_square(tmp, y_in);
    felem_reduce(gamma, tmp);

    /* beta = x*gamma */
    felem_mul(tmp, x_in, gamma);
    felem_reduce(beta, tmp);

    /* alpha = 3*(x-delta)*(x+delta) */
    felem_diff(ftmp, delta);
    /* ftmp[i] < 2^57 + 2^58 + 2 < 2^59 */
    felem_sum(ftmp2, delta);
    /* ftmp2[i] < 2^57 + 2^57 = 2^58 */
    felem_scalar(ftmp2, 3);
    /* ftmp2[i] < 3 * 2^58 < 2^60 */
    felem_mul(tmp, ftmp, ftmp2);
    /* tmp[i] < 2^60 * 2^59 * 4 = 2^121 */
    felem_reduce(alpha, tmp);

    /* x' = alpha^2 - 8*beta */
    felem_square(tmp, alpha);
    /* tmp[i] < 4 * 2^57 * 2^57 = 2^116 */
    felem_assign(ftmp, beta);
    felem_scalar(ftmp, 8);
    /* ftmp[i] < 8 * 2^57 = 2^60 */
    felem_diff_128_64(tmp, ftmp);
    /* tmp[i] < 2^116 + 2^64 + 8 < 2^117 */
    felem_reduce(x_out, tmp);

    /* z' = (y + z)^2 - gamma - delta */
    felem_sum(delta, gamma);
    /* delta[i] < 2^57 + 2^57 = 2^58 */
    felem_assign(ftmp, y_in);
    felem_sum(ftmp, z_in);
    /* ftmp[i] < 2^57 + 2^57 = 2^58 */
    felem_square(tmp, ftmp);
    /* tmp[i] < 4 * 2^58 * 2^58 = 2^118 */
    felem_diff_128_64(tmp, delta);
    /* tmp[i] < 2^118 + 2^64 + 8 < 2^119 */
    felem_reduce(z_out, tmp);

    /* y' = alpha*(4*beta - x') - 8*gamma^2 */
    felem_scalar(beta, 4);
    /* beta[i] < 4 * 2^57 = 2^59 */
    felem_diff(beta, x_out);
    /* beta[i] < 2^59 + 2^58 + 2 < 2^60 */
    felem_mul(tmp, alpha, beta);
    /* tmp[i] < 4 * 2^57 * 2^60 = 2^119 */
    felem_square(tmp2, gamma);
    /* tmp2[i] < 4 * 2^57 * 2^57 = 2^116 */
    widefelem_scalar(tmp2, 8);
    /* tmp2[i] < 8 * 2^116 = 2^119 */
    widefelem_diff(tmp, tmp2);
    /* tmp[i] < 2^119 + 2^120 < 2^121 */
    felem_reduce(y_out, tmp);
}