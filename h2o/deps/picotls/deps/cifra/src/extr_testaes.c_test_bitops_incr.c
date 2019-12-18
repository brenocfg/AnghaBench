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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_BE (int,int,int) ; 
 int /*<<< orphan*/  CHECK_LE (int,int,int) ; 

__attribute__((used)) static void test_bitops_incr(void)
{
  uint8_t buf[4];

#define CHECK_BE(start, add, end) \
  { \
    write32_be((start), buf); \
    for (size_t i = 0; i < (add); i++) \
      incr_be(buf, sizeof buf); \
    TEST_CHECK(read32_be(buf) == (end)); \
  }

#define CHECK_LE(start, add, end) \
  { \
    write32_le((start), buf); \
    for (size_t i = 0; i < (add); i++) \
      incr_le(buf, sizeof buf); \
    TEST_CHECK(read32_le(buf) == (end)); \
  }

  CHECK_BE(0, 1, 1);
  CHECK_BE(0, 256, 256);
  CHECK_BE(256, 256, 512);
  CHECK_BE(0xffffffff, 1, 0);

  CHECK_LE(0, 1, 1);
  CHECK_LE(0, 256, 256);
  CHECK_LE(0x7fffffff, 1, 0x80000000);
  CHECK_LE(0xffffffff, 1, 0);

#undef CHECK_BE
#undef CHECK_LE
}