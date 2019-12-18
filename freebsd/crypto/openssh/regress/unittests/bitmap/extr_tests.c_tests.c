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
typedef  int /*<<< orphan*/  u_char ;
struct bitmap {int dummy; } ;
typedef  int /*<<< orphan*/  bbuf ;
typedef  struct bitmap BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int,int) ; 
 int /*<<< orphan*/  ASSERT_INT_GE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_MEM_EQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct bitmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT_U8_EQ (int /*<<< orphan*/ ,int) ; 
 int BN_bn2bin (struct bitmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (struct bitmap*) ; 
 int /*<<< orphan*/  BN_clear_bit (struct bitmap*,int) ; 
 int /*<<< orphan*/  BN_free (struct bitmap*) ; 
 int BN_is_bit_set (struct bitmap*,int) ; 
 struct bitmap* BN_new () ; 
 int BN_num_bits (struct bitmap*) ; 
 int BN_num_bytes (struct bitmap*) ; 
 int BN_set_bit (struct bitmap*,int) ; 
 int NTESTS ; 
 int /*<<< orphan*/  TEST_DONE () ; 
 int /*<<< orphan*/  TEST_START (char*) ; 
 int /*<<< orphan*/  bitmap_clear_bit (struct bitmap*,int) ; 
 int /*<<< orphan*/  bitmap_free (struct bitmap*) ; 
 int bitmap_from_string (struct bitmap*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ bitmap_nbits (struct bitmap*) ; 
 size_t bitmap_nbytes (struct bitmap*) ; 
 struct bitmap* bitmap_new () ; 
 int bitmap_set_bit (struct bitmap*,int) ; 
 int bitmap_test_bit (struct bitmap*,int) ; 
 int bitmap_to_string (struct bitmap*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_zero (struct bitmap*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  test_subtest_info (char*,int,int,int) ; 

void
tests(void)
{
	struct bitmap *b;
	BIGNUM *bn;
	size_t len;
	int i, j, k, n;
	u_char bbuf[1024], bnbuf[1024];
	int r;

	TEST_START("bitmap_new");
	b = bitmap_new();
	ASSERT_PTR_NE(b, NULL);
	bn = BN_new();
	ASSERT_PTR_NE(bn, NULL);
	TEST_DONE();

	TEST_START("bitmap_set_bit / bitmap_test_bit");
	for (i = -1; i < NTESTS; i++) {
		for (j = -1; j < NTESTS; j++) {
			for (k = -1; k < NTESTS; k++) {
				bitmap_zero(b);
				BN_clear(bn);

				test_subtest_info("set %d/%d/%d", i, j, k);
				/* Set bits */
				if (i >= 0) {
					ASSERT_INT_EQ(bitmap_set_bit(b, i), 0);
					ASSERT_INT_EQ(BN_set_bit(bn, i), 1);
				}
				if (j >= 0) {
					ASSERT_INT_EQ(bitmap_set_bit(b, j), 0);
					ASSERT_INT_EQ(BN_set_bit(bn, j), 1);
				}
				if (k >= 0) {
					ASSERT_INT_EQ(bitmap_set_bit(b, k), 0);
					ASSERT_INT_EQ(BN_set_bit(bn, k), 1);
				}

				/* Check perfect match between bitmap and bn */
				test_subtest_info("match %d/%d/%d", i, j, k);
				for (n = 0; n < NTESTS; n++) {
					ASSERT_INT_EQ(BN_is_bit_set(bn, n),
					    bitmap_test_bit(b, n));
				}

				/* Test length calculations */
				test_subtest_info("length %d/%d/%d", i, j, k);
				ASSERT_INT_EQ(BN_num_bits(bn),
				    (int)bitmap_nbits(b));
				ASSERT_INT_EQ(BN_num_bytes(bn),
				    (int)bitmap_nbytes(b));

				/* Test serialisation */
				test_subtest_info("serialise %d/%d/%d",
				    i, j, k);
				len = bitmap_nbytes(b);
				memset(bbuf, 0xfc, sizeof(bbuf));
				ASSERT_INT_EQ(bitmap_to_string(b, bbuf,
				    sizeof(bbuf)), 0);
				for (n = len; n < (int)sizeof(bbuf); n++)
					ASSERT_U8_EQ(bbuf[n], 0xfc);
				r = BN_bn2bin(bn, bnbuf);
				ASSERT_INT_GE(r, 0);
				ASSERT_INT_EQ(r, (int)len);
				ASSERT_MEM_EQ(bbuf, bnbuf, len);

				/* Test deserialisation */
				test_subtest_info("deserialise %d/%d/%d",
				    i, j, k);
				bitmap_zero(b);
				ASSERT_INT_EQ(bitmap_from_string(b, bnbuf,
				    len), 0);
				for (n = 0; n < NTESTS; n++) {
					ASSERT_INT_EQ(BN_is_bit_set(bn, n),
					    bitmap_test_bit(b, n));
				}

				/* Test clearing bits */
				test_subtest_info("clear %d/%d/%d",
				    i, j, k);
				for (n = 0; n < NTESTS; n++) {
					ASSERT_INT_EQ(bitmap_set_bit(b, n), 0);
					ASSERT_INT_EQ(BN_set_bit(bn, n), 1);
				}
				if (i >= 0) {
					bitmap_clear_bit(b, i);
					BN_clear_bit(bn, i);
				}
				if (j >= 0) {
					bitmap_clear_bit(b, j);
					BN_clear_bit(bn, j);
				}
				if (k >= 0) {
					bitmap_clear_bit(b, k);
					BN_clear_bit(bn, k);
				}
				for (n = 0; n < NTESTS; n++) {
					ASSERT_INT_EQ(BN_is_bit_set(bn, n),
					    bitmap_test_bit(b, n));
				}
			}
		}
	}
	bitmap_free(b);
	BN_free(bn);
	TEST_DONE();
}