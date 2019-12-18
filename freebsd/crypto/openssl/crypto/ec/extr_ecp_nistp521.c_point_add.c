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
typedef  scalar_t__ limb ;
typedef  int /*<<< orphan*/  largefelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  copy_conditional (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_diff64 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_128_64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ felem_is_zero (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_scalar128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  felem_scalar64 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_sum64 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void point_add(felem x3, felem y3, felem z3,
                      const felem x1, const felem y1, const felem z1,
                      const int mixed, const felem x2, const felem y2,
                      const felem z2)
{
    felem ftmp, ftmp2, ftmp3, ftmp4, ftmp5, ftmp6, x_out, y_out, z_out;
    largefelem tmp, tmp2;
    limb x_equal, y_equal, z1_is_zero, z2_is_zero;

    z1_is_zero = felem_is_zero(z1);
    z2_is_zero = felem_is_zero(z2);

    /* ftmp = z1z1 = z1**2 */
    felem_square(tmp, z1);
    felem_reduce(ftmp, tmp);

    if (!mixed) {
        /* ftmp2 = z2z2 = z2**2 */
        felem_square(tmp, z2);
        felem_reduce(ftmp2, tmp);

        /* u1 = ftmp3 = x1*z2z2 */
        felem_mul(tmp, x1, ftmp2);
        felem_reduce(ftmp3, tmp);

        /* ftmp5 = z1 + z2 */
        felem_assign(ftmp5, z1);
        felem_sum64(ftmp5, z2);
        /* ftmp5[i] < 2^61 */

        /* ftmp5 = (z1 + z2)**2 - z1z1 - z2z2 = 2*z1z2 */
        felem_square(tmp, ftmp5);
        /* tmp[i] < 17*2^122 */
        felem_diff_128_64(tmp, ftmp);
        /* tmp[i] < 17*2^122 + 2^63 */
        felem_diff_128_64(tmp, ftmp2);
        /* tmp[i] < 17*2^122 + 2^64 */
        felem_reduce(ftmp5, tmp);

        /* ftmp2 = z2 * z2z2 */
        felem_mul(tmp, ftmp2, z2);
        felem_reduce(ftmp2, tmp);

        /* s1 = ftmp6 = y1 * z2**3 */
        felem_mul(tmp, y1, ftmp2);
        felem_reduce(ftmp6, tmp);
    } else {
        /*
         * We'll assume z2 = 1 (special case z2 = 0 is handled later)
         */

        /* u1 = ftmp3 = x1*z2z2 */
        felem_assign(ftmp3, x1);

        /* ftmp5 = 2*z1z2 */
        felem_scalar(ftmp5, z1, 2);

        /* s1 = ftmp6 = y1 * z2**3 */
        felem_assign(ftmp6, y1);
    }

    /* u2 = x2*z1z1 */
    felem_mul(tmp, x2, ftmp);
    /* tmp[i] < 17*2^120 */

    /* h = ftmp4 = u2 - u1 */
    felem_diff_128_64(tmp, ftmp3);
    /* tmp[i] < 17*2^120 + 2^63 */
    felem_reduce(ftmp4, tmp);

    x_equal = felem_is_zero(ftmp4);

    /* z_out = ftmp5 * h */
    felem_mul(tmp, ftmp5, ftmp4);
    felem_reduce(z_out, tmp);

    /* ftmp = z1 * z1z1 */
    felem_mul(tmp, ftmp, z1);
    felem_reduce(ftmp, tmp);

    /* s2 = tmp = y2 * z1**3 */
    felem_mul(tmp, y2, ftmp);
    /* tmp[i] < 17*2^120 */

    /* r = ftmp5 = (s2 - s1)*2 */
    felem_diff_128_64(tmp, ftmp6);
    /* tmp[i] < 17*2^120 + 2^63 */
    felem_reduce(ftmp5, tmp);
    y_equal = felem_is_zero(ftmp5);
    felem_scalar64(ftmp5, 2);
    /* ftmp5[i] < 2^61 */

    if (x_equal && y_equal && !z1_is_zero && !z2_is_zero) {
        /*
         * This is obviously not constant-time but it will almost-never happen
         * for ECDH / ECDSA. The case where it can happen is during scalar-mult
         * where the intermediate value gets very close to the group order.
         * Since |ec_GFp_nistp_recode_scalar_bits| produces signed digits for
         * the scalar, it's possible for the intermediate value to be a small
         * negative multiple of the base point, and for the final signed digit
         * to be the same value. We believe that this only occurs for the scalar
         * 1fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
         * ffffffa51868783bf2f966b7fcc0148f709a5d03bb5c9b8899c47aebb6fb
         * 71e913863f7, in that case the penultimate intermediate is -9G and
         * the final digit is also -9G. Since this only happens for a single
         * scalar, the timing leak is irrelevant. (Any attacker who wanted to
         * check whether a secret scalar was that exact value, can already do
         * so.)
         */
        point_double(x3, y3, z3, x1, y1, z1);
        return;
    }

    /* I = ftmp = (2h)**2 */
    felem_assign(ftmp, ftmp4);
    felem_scalar64(ftmp, 2);
    /* ftmp[i] < 2^61 */
    felem_square(tmp, ftmp);
    /* tmp[i] < 17*2^122 */
    felem_reduce(ftmp, tmp);

    /* J = ftmp2 = h * I */
    felem_mul(tmp, ftmp4, ftmp);
    felem_reduce(ftmp2, tmp);

    /* V = ftmp4 = U1 * I */
    felem_mul(tmp, ftmp3, ftmp);
    felem_reduce(ftmp4, tmp);

    /* x_out = r**2 - J - 2V */
    felem_square(tmp, ftmp5);
    /* tmp[i] < 17*2^122 */
    felem_diff_128_64(tmp, ftmp2);
    /* tmp[i] < 17*2^122 + 2^63 */
    felem_assign(ftmp3, ftmp4);
    felem_scalar64(ftmp4, 2);
    /* ftmp4[i] < 2^61 */
    felem_diff_128_64(tmp, ftmp4);
    /* tmp[i] < 17*2^122 + 2^64 */
    felem_reduce(x_out, tmp);

    /* y_out = r(V-x_out) - 2 * s1 * J */
    felem_diff64(ftmp3, x_out);
    /*
     * ftmp3[i] < 2^60 + 2^60 = 2^61
     */
    felem_mul(tmp, ftmp5, ftmp3);
    /* tmp[i] < 17*2^122 */
    felem_mul(tmp2, ftmp6, ftmp2);
    /* tmp2[i] < 17*2^120 */
    felem_scalar128(tmp2, 2);
    /* tmp2[i] < 17*2^121 */
    felem_diff128(tmp, tmp2);
        /*-
         * tmp[i] < 2^127 - 2^69 + 17*2^122
         *        = 2^126 - 2^122 - 2^6 - 2^2 - 1
         *        < 2^127
         */
    felem_reduce(y_out, tmp);

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