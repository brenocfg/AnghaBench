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
typedef  int /*<<< orphan*/  cf_gf128 ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_gf128_frombytes_be (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_tobytes_be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_gf128_mul(void)
{
  uint8_t bout[16];

  const void *bx = "\x03\x88\xda\xce\x60\xb6\xa3\x92\xf3\x28\xc2\xb9\x71\xb2\xfe\x78";
  const void *by = "\x66\xe9\x4b\xd4\xef\x8a\x2c\x3b\x88\x4c\xfa\x59\xca\x34\x2b\x2e";
  const void *bexpect = "\x5e\x2e\xc7\x46\x91\x70\x62\x88\x2c\x85\xb0\x68\x53\x53\xde\xb7";

  cf_gf128 x, y, out;
  cf_gf128_frombytes_be(bx, x);
  cf_gf128_frombytes_be(by, y);
  cf_gf128_mul(x, y, out);
  cf_gf128_tobytes_be(out, bout);
  TEST_CHECK(memcmp(bexpect, bout, 16) == 0);
}