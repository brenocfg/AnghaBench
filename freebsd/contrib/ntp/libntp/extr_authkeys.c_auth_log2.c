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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int CHAR_BIT ; 

__attribute__((used)) static u_short
auth_log2(size_t x)
{
	/*
	** bithack to calculate floor(log2(x))
	**
	** This assumes
	**   - (sizeof(size_t) is a power of two
	**   - CHAR_BITS is a power of two
	**   - returning zero for arguments <= 0 is OK.
	**
	** Does only shifts, masks and sums in integer arithmetic in
	** log2(CHAR_BIT*sizeof(size_t)) steps. (that is, 5/6 steps for
	** 32bit/64bit size_t)
	*/
	int	s;
	int	r = 0;
	size_t  m = ~(size_t)0;

	for (s = sizeof(size_t) / 2 * CHAR_BIT; s != 0; s >>= 1) {
		m <<= s;
		if (x & m)
			r += s;
		else
			x <<= s;
	}
	return (u_short)r;
}