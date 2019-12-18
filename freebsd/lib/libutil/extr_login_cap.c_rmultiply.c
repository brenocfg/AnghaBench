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
typedef  int u_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int UQUAD_MAX ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static u_quad_t
rmultiply(u_quad_t n1, u_quad_t n2)
{
    u_quad_t	m, r;
    int		b1, b2;

    static int bpw = 0;

    /* Handle simple cases */
    if (n1 == 0 || n2 == 0)
	return 0;
    if (n1 == 1)
	return n2;
    if (n2 == 1)
	return n1;

    /*
     * sizeof() returns number of bytes needed for storage.
     * This may be different from the actual number of useful bits.
     */
    if (!bpw) {
	bpw = sizeof(u_quad_t) * 8;
	while (((u_quad_t)1 << (bpw-1)) == 0)
	    --bpw;
    }

    /*
     * First check the magnitude of each number. If the sum of the
     * magnatude is way to high, reject the number. (If this test
     * is not done then the first multiply below may overflow.)
     */
    for (b1 = bpw; (((u_quad_t)1 << (b1-1)) & n1) == 0; --b1)
	; 
    for (b2 = bpw; (((u_quad_t)1 << (b2-1)) & n2) == 0; --b2)
	; 
    if (b1 + b2 - 2 > bpw) {
	errno = ERANGE;
	return (UQUAD_MAX);
    }

    /*
     * Decompose the multiplication to be:
     * h1 = n1 & ~1
     * h2 = n2 & ~1
     * l1 = n1 & 1
     * l2 = n2 & 1
     * (h1 + l1) * (h2 + l2)
     * (h1 * h2) + (h1 * l2) + (l1 * h2) + (l1 * l2)
     *
     * Since h1 && h2 do not have the low bit set, we can then say:
     *
     * (h1>>1 * h2>>1 * 4) + ...
     *
     * So if (h1>>1 * h2>>1) > (1<<(bpw - 2)) then the result will
     * overflow.
     *
     * Finally, if MAX - ((h1 * l2) + (l1 * h2) + (l1 * l2)) < (h1*h2)
     * then adding in residual amout will cause an overflow.
     */

    m = (n1 >> 1) * (n2 >> 1);
    if (m >= ((u_quad_t)1 << (bpw-2))) {
	errno = ERANGE;
	return (UQUAD_MAX);
    }
    m *= 4;

    r = (n1 & n2 & 1)
	+ (n2 & 1) * (n1 & ~(u_quad_t)1)
	+ (n1 & 1) * (n2 & ~(u_quad_t)1);

    if ((u_quad_t)(m + r) < m) {
	errno = ERANGE;
	return (UQUAD_MAX);
    }
    m += r;

    return (m);
}