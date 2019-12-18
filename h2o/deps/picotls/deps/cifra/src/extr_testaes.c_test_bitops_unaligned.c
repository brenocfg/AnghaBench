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
 int /*<<< orphan*/  CHECK (int,int,int) ; 
 int /*<<< orphan*/  write32_be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_bitops_unaligned(void)
{
  uint8_t in[4], out[4];

#define CHECK(outw, len, offs) \
  { \
    memset(out, 0, sizeof out); \
    copy_bytes_unaligned(out, in, len, offs); \
    TEST_CHECK(read32_be(out) == (outw)); \
  }

  write32_be(0x11223344, in);

  CHECK(0x11223344, 4, 0);
  CHECK(0x22446600, 3, 1);
  CHECK(0x4488cd00, 3, 2);
  CHECK(0x89119a00, 3, 3);
  CHECK(0x12233400, 3, 4);
  CHECK(0x24466800, 3, 5);
  CHECK(0x488cd100, 3, 6);
  CHECK(0x9119a200, 3, 7);
  CHECK(0x22334400, 3, 8);
  CHECK(0x44660000, 2, 9);
  CHECK(0x33440000, 2, 16);

#undef CHECK
}