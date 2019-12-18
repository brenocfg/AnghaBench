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
typedef  int uint8_t ;

/* Variables and functions */
 int memcmp (int const*,int const*,size_t) ; 

__attribute__((used)) static int bmemcmp(const void *av, const void *bv, size_t bits)
{
	const uint8_t *a = av, *b = bv;
	size_t bytes = bits / 8;
	bits %= 8;

	int res = memcmp(a, b, bytes);
	if (res == 0 && bits > 0)
		res = (a[bytes] >> (8 - bits)) - (b[bytes] >> (8 - bits));

	return res;
}