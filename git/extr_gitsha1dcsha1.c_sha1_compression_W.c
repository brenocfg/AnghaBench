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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HASHCLASH_SHA1COMPRESS_ROUND1_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  HASHCLASH_SHA1COMPRESS_ROUND2_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  HASHCLASH_SHA1COMPRESS_ROUND3_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  HASHCLASH_SHA1COMPRESS_ROUND4_STEP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__ const*,int) ; 

__attribute__((used)) static void sha1_compression_W(uint32_t ihv[5], const uint32_t W[80])
{
	uint32_t a = ihv[0], b = ihv[1], c = ihv[2], d = ihv[3], e = ihv[4];

	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(a, b, c, d, e, W, 0);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(e, a, b, c, d, W, 1);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(d, e, a, b, c, W, 2);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(c, d, e, a, b, W, 3);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(b, c, d, e, a, W, 4);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(a, b, c, d, e, W, 5);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(e, a, b, c, d, W, 6);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(d, e, a, b, c, W, 7);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(c, d, e, a, b, W, 8);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(b, c, d, e, a, W, 9);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(a, b, c, d, e, W, 10);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(e, a, b, c, d, W, 11);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(d, e, a, b, c, W, 12);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(c, d, e, a, b, W, 13);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(b, c, d, e, a, W, 14);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(a, b, c, d, e, W, 15);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(e, a, b, c, d, W, 16);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(d, e, a, b, c, W, 17);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(c, d, e, a, b, W, 18);
	HASHCLASH_SHA1COMPRESS_ROUND1_STEP(b, c, d, e, a, W, 19);

	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(a, b, c, d, e, W, 20);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(e, a, b, c, d, W, 21);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(d, e, a, b, c, W, 22);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(c, d, e, a, b, W, 23);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(b, c, d, e, a, W, 24);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(a, b, c, d, e, W, 25);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(e, a, b, c, d, W, 26);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(d, e, a, b, c, W, 27);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(c, d, e, a, b, W, 28);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(b, c, d, e, a, W, 29);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(a, b, c, d, e, W, 30);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(e, a, b, c, d, W, 31);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(d, e, a, b, c, W, 32);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(c, d, e, a, b, W, 33);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(b, c, d, e, a, W, 34);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(a, b, c, d, e, W, 35);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(e, a, b, c, d, W, 36);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(d, e, a, b, c, W, 37);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(c, d, e, a, b, W, 38);
	HASHCLASH_SHA1COMPRESS_ROUND2_STEP(b, c, d, e, a, W, 39);

	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(a, b, c, d, e, W, 40);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(e, a, b, c, d, W, 41);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(d, e, a, b, c, W, 42);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(c, d, e, a, b, W, 43);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(b, c, d, e, a, W, 44);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(a, b, c, d, e, W, 45);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(e, a, b, c, d, W, 46);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(d, e, a, b, c, W, 47);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(c, d, e, a, b, W, 48);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(b, c, d, e, a, W, 49);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(a, b, c, d, e, W, 50);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(e, a, b, c, d, W, 51);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(d, e, a, b, c, W, 52);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(c, d, e, a, b, W, 53);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(b, c, d, e, a, W, 54);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(a, b, c, d, e, W, 55);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(e, a, b, c, d, W, 56);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(d, e, a, b, c, W, 57);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(c, d, e, a, b, W, 58);
	HASHCLASH_SHA1COMPRESS_ROUND3_STEP(b, c, d, e, a, W, 59);

	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(a, b, c, d, e, W, 60);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(e, a, b, c, d, W, 61);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(d, e, a, b, c, W, 62);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(c, d, e, a, b, W, 63);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(b, c, d, e, a, W, 64);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(a, b, c, d, e, W, 65);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(e, a, b, c, d, W, 66);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(d, e, a, b, c, W, 67);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(c, d, e, a, b, W, 68);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(b, c, d, e, a, W, 69);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(a, b, c, d, e, W, 70);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(e, a, b, c, d, W, 71);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(d, e, a, b, c, W, 72);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(c, d, e, a, b, W, 73);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(b, c, d, e, a, W, 74);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(a, b, c, d, e, W, 75);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(e, a, b, c, d, W, 76);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(d, e, a, b, c, W, 77);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(c, d, e, a, b, W, 78);
	HASHCLASH_SHA1COMPRESS_ROUND4_STEP(b, c, d, e, a, W, 79);

	ihv[0] += a; ihv[1] += b; ihv[2] += c; ihv[3] += d; ihv[4] += e;
}