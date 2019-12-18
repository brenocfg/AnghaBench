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
struct gf128table4 {int /*<<< orphan*/ * tbls; } ;
struct gf128 {int* v; } ;

/* Variables and functions */
 struct gf128 gf128_add (struct gf128,struct gf128) ; 
 struct gf128 readrow (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__* reduction ; 

__attribute__((used)) static struct gf128
gfmultword4(uint64_t worda, uint64_t wordb, uint64_t wordc, uint64_t wordd,
    struct gf128 x, struct gf128table4 *tbl)
{
	struct gf128 rowa, rowb, rowc, rowd;
	unsigned bitsa, bitsb, bitsc, bitsd;
	unsigned redbits;
	int i;

	/*
	 * XXX - nibble reverse words to save a shift? probably not as
	 * nibble reverse would take 20 ops (5 * 4) verse 16
	 */

	for (i = 0; i < 64; i += 4) {
		bitsa = worda % 16;
		bitsb = wordb % 16;
		bitsc = wordc % 16;
		bitsd = wordd % 16;

		/* fetch row */
		rowa = readrow(&tbl->tbls[3], bitsa);
		rowb = readrow(&tbl->tbls[2], bitsb);
		rowc = readrow(&tbl->tbls[1], bitsc);
		rowd = readrow(&tbl->tbls[0], bitsd);

		/* x * 2^4 */
		redbits = x.v[1] % 16;
		x.v[1] = (x.v[1] >> 4) | (x.v[0] % 16) << 60;
		x.v[0] >>= 4;
		x.v[0] ^= (uint64_t)reduction[redbits] << (64 - 16);

		worda >>= 4;
		wordb >>= 4;
		wordc >>= 4;
		wordd >>= 4;

		x = gf128_add(x, gf128_add(rowa, gf128_add(rowb,
		    gf128_add(rowc, rowd))));
	}

	return x;
}