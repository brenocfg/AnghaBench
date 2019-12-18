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
typedef  scalar_t__ limb ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  copy_conditional (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_128_64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ felem_is_zero (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  widefelem_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void point_add(felem x3, felem y3, felem z3,
                      const felem x1, const felem y1, const felem z1,
                      const int mixed, const felem x2, const felem y2,
                      const felem z2)
{
    felem ftmp, ftmp2, ftmp3, ftmp4, ftmp5, x_out, y_out, z_out;
    widefelem tmp, tmp2;
    limb z1_is_zero, z2_is_zero, x_equal, y_equal;

    if (!mixed) {
        /* ftmp2 = z2^2 */
        felem_square(tmp, z2);
        felem_reduce(ftmp2, tmp);

        /* ftmp4 = z2^3 */
        felem_mul(tmp, ftmp2, z2);
        felem_reduce(ftmp4, tmp);

        /* ftmp4 = z2^3*y1 */
        felem_mul(tmp2, ftmp4, y1);
        felem_reduce(ftmp4, tmp2);

        /* ftmp2 = z2^2*x1 */
        felem_mul(tmp2, ftmp2, x1);
        felem_reduce(ftmp2, tmp2);
    } else {
        /*
         * We'll assume z2 = 1 (special case z2 = 0 is handled later)
         */

        /* ftmp4 = z2^3*y1 */
        felem_assign(ftmp4, y1);

        /* ftmp2 = z2^2*x1 */
        felem_assign(ftmp2, x1);
    }

    /* ftmp = z1^2 */
    felem_square(tmp, z1);
    felem_reduce(ftmp, tmp);

    /* ftmp3 = z1^3 */
    felem_mul(tmp, ftmp, z1);
    felem_reduce(ftmp3, tmp);

    /* tmp = z1^3*y2 */
    felem_mul(tmp, ftmp3, y2);
    /* tmp[i] < 4 * 2^57 * 2^57 = 2^116 */

    /* ftmp3 = z1^3*y2 - z2^3*y1 */
    felem_diff_128_64(tmp, ftmp4);
    /* tmp[i] < 2^116 + 2^64 + 8 < 2^117 */
    felem_reduce(ftmp3, tmp);

    /* tmp = z1^2*x2 */
    felem_mul(tmp, ftmp, x2);
    /* tmp[i] < 4 * 2^57 * 2^57 = 2^116 */

    /* ftmp = z1^2*x2 - z2^2*x1 */
    felem_diff_128_64(tmp, ftmp2);
    /* tmp[i] < 2^116 + 2^64 + 8 < 2^117 */
    felem_reduce(ftmp, tmp);

    /*
     * the formulae are incorrect if the points are equal so we check for
     * this and do doubling if this happens
     */
    x_equal = felem_is_zero(ftmp);
    y_equal = felem_is_zero(ftmp3);
    z1_is_zero = felem_is_zero(z1);
    z2_is_zero = felem_is_zero(z2);
    /* In affine coordinates, (X_1, Y_1) == (X_2, Y_2) */
    if (x_equal && y_equal && !z1_is_zero && !z2_is_zero) {
        point_double(x3, y3, z3, x1, y1, z1);
        return;
    }

    /* ftmp5 = z1*z2 */
    if (!mixed) {
        felem_mul(tmp, z1, z2);
        felem_reduce(ftmp5, tmp);
    } else {
        /* special case z2 = 0 is handled later */
        felem_assign(ftmp5, z1);
    }

    /* z_out = (z1^2*x2 - z2^2*x1)*(z1*z2) */
    felem_mul(tmp, ftmp, ftmp5);
    felem_reduce(z_out, tmp);

    /* ftmp = (z1^2*x2 - z2^2*x1)^2 */
    felem_assign(ftmp5, ftmp);
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);

    /* ftmp5 = (z1^2*x2 - z2^2*x1)^3 */
    felem_mul(tmp, ftmp, ftmp5);
    felem_reduce(ftmp5, tmp);

    /* ftmp2 = z2^2*x1*(z1^2*x2 - z2^2*x1)^2 */
    felem_mul(tmp, ftmp2, ftmp);
    felem_reduce(ftmp2, tmp);

    /* tmp = z2^3*y1*(z1^2*x2 - z2^2*x1)^3 */
    felem_mul(tmp, ftmp4, ftmp5);
    /* tmp[i] < 4 * 2^57 * 2^57 = 2^116 */

    /* tmp2 = (z1^3*y2 - z2^3*y1)^2 */
    felem_square(tmp2, ftmp3);
    /* tmp2[i] < 4 * 2^57 * 2^57 < 2^116 */

    /* tmp2 = (z1^3*y2 - z2^3*y1)^2 - (z1^2*x2 - z2^2*x1)^3 */
    felem_diff_128_64(tmp2, ftmp5);
    /* tmp2[i] < 2^116 + 2^64 + 8 < 2^117 */

    /* ftmp5 = 2*z2^2*x1*(z1^2*x2 - z2^2*x1)^2 */
    felem_assign(ftmp5, ftmp2);
    felem_scalar(ftmp5, 2);
    /* ftmp5[i] < 2 * 2^57 = 2^58 */

    /*-
     * x_out = (z1^3*y2 - z2^3*y1)^2 - (z1^2*x2 - z2^2*x1)^3 -
     *  2*z2^2*x1*(z1^2*x2 - z2^2*x1)^2
     */
    felem_diff_128_64(tmp2, ftmp5);
    /* tmp2[i] < 2^117 + 2^64 + 8 < 2^118 */
    felem_reduce(x_out, tmp2);

    /* ftmp2 = z2^2*x1*(z1^2*x2 - z2^2*x1)^2 - x_out */
    felem_diff(ftmp2, x_out);
    /* ftmp2[i] < 2^57 + 2^58 + 2 < 2^59 */

    /*
     * tmp2 = (z1^3*y2 - z2^3*y1)*(z2^2*x1*(z1^2*x2 - z2^2*x1)^2 - x_out)
     */
    felem_mul(tmp2, ftmp3, ftmp2);
    /* tmp2[i] < 4 * 2^57 * 2^59 = 2^118 */

    /*-
     * y_out = (z1^3*y2 - z2^3*y1)*(z2^2*x1*(z1^2*x2 - z2^2*x1)^2 - x_out) -
     *  z2^3*y1*(z1^2*x2 - z2^2*x1)^3
     */
    widefelem_diff(tmp2, tmp);
    /* tmp2[i] < 2^118 + 2^120 < 2^121 */
    felem_reduce(y_out, tmp2);

    /*
     * the result (x_out, y_out, z_out) is incorrect if one of the inputs is
     * the point at infinity, so we need to check for this separately
     */

    /*
     * if point 1 is at infinity, copy point 2 to output, and vice versa
     */
    copy_conditional(x_out, x2, z1_is_zero);
    copy_conditional(x_out, x1, z2_is_zero);
    copy_conditional(y_out, y2, z1_is_zero);
    copy_conditional(y_out, y1, z2_is_zero);
    copy_conditional(z_out, z2, z1_is_zero);
    copy_conditional(z_out, z1, z2_is_zero);
    felem_assign(x3, x_out);
    felem_assign(y3, y_out);
    felem_assign(z3, z_out);
}