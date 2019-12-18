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
typedef  int /*<<< orphan*/  const fe51 ;

/* Variables and functions */
 int /*<<< orphan*/  fe51_mul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe51_sq (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void fe51_invert(fe51 out, const fe51 z)
{
    fe51 t0;
    fe51 t1;
    fe51 t2;
    fe51 t3;
    int i;

    /*
     * Compute z ** -1 = z ** (2 ** 255 - 19 - 2) with the exponent as
     * 2 ** 255 - 21 = (2 ** 5) * (2 ** 250 - 1) + 11.
     */

    /* t0 = z ** 2 */
    fe51_sq(t0, z);

    /* t1 = t0 ** (2 ** 2) = z ** 8 */
    fe51_sq(t1, t0);
    fe51_sq(t1, t1);

    /* t1 = z * t1 = z ** 9 */
    fe51_mul(t1, z, t1);
    /* t0 = t0 * t1 = z ** 11 -- stash t0 away for the end. */
    fe51_mul(t0, t0, t1);

    /* t2 = t0 ** 2 = z ** 22 */
    fe51_sq(t2, t0);

    /* t1 = t1 * t2 = z ** (2 ** 5 - 1) */
    fe51_mul(t1, t1, t2);

    /* t2 = t1 ** (2 ** 5) = z ** ((2 ** 5) * (2 ** 5 - 1)) */
    fe51_sq(t2, t1);
    for (i = 1; i < 5; ++i)
        fe51_sq(t2, t2);

    /* t1 = t1 * t2 = z ** ((2 ** 5 + 1) * (2 ** 5 - 1)) = z ** (2 ** 10 - 1) */
    fe51_mul(t1, t2, t1);

    /* Continuing similarly... */

    /* t2 = z ** (2 ** 20 - 1) */
    fe51_sq(t2, t1);
    for (i = 1; i < 10; ++i)
        fe51_sq(t2, t2);

    fe51_mul(t2, t2, t1);

    /* t2 = z ** (2 ** 40 - 1) */
    fe51_sq(t3, t2);
    for (i = 1; i < 20; ++i)
        fe51_sq(t3, t3);

    fe51_mul(t2, t3, t2);

    /* t2 = z ** (2 ** 10) * (2 ** 40 - 1) */
    for (i = 0; i < 10; ++i)
        fe51_sq(t2, t2);

    /* t1 = z ** (2 ** 50 - 1) */
    fe51_mul(t1, t2, t1);

    /* t2 = z ** (2 ** 100 - 1) */
    fe51_sq(t2, t1);
    for (i = 1; i < 50; ++i)
        fe51_sq(t2, t2);

    fe51_mul(t2, t2, t1);

    /* t2 = z ** (2 ** 200 - 1) */
    fe51_sq(t3, t2);
    for (i = 1; i < 100; ++i)
        fe51_sq(t3, t3);

    fe51_mul(t2, t3, t2);

    /* t2 = z ** ((2 ** 50) * (2 ** 200 - 1) */
    for (i = 0; i < 50; ++i)
        fe51_sq(t2, t2);

    /* t1 = z ** (2 ** 250 - 1) */
    fe51_mul(t1, t2, t1);

    /* t1 = z ** ((2 ** 5) * (2 ** 250 - 1)) */
    for (i = 0; i < 5; ++i)
        fe51_sq(t1, t1);

    /* Recall t0 = z ** 11; out = z ** (2 ** 255 - 21) */
    fe51_mul(out, t1, t0);
}