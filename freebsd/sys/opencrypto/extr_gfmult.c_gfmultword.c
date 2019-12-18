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
typedef  int uint64_t ;
struct gf128table {int dummy; } ;
struct gf128 {int* v; } ;

/* Variables and functions */
 struct gf128 gf128_add (struct gf128,struct gf128) ; 
 struct gf128 readrow (struct gf128table*,unsigned int) ; 
 scalar_t__* reduction ; 

__attribute__((used)) static struct gf128
gfmultword(uint64_t word, struct gf128 x, struct gf128table *tbl)
{
	struct gf128 row;
	unsigned bits;
	unsigned redbits;
	int i;

	for (i = 0; i < 64; i += 4) {
		bits = word % 16;

		/* fetch row */
		row = readrow(tbl, bits);

		/* x * 2^4 */
		redbits = x.v[1] % 16;
		x.v[1] = (x.v[1] >> 4) | (x.v[0] % 16) << 60;
		x.v[0] >>= 4;
		x.v[0] ^= (uint64_t)reduction[redbits] << (64 - 16);

		word >>= 4;

		x = gf128_add(x, row);
	}

	return x;
}