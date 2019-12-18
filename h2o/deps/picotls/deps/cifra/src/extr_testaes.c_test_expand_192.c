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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYCOUNT (int const*) ; 
 int /*<<< orphan*/  test_expand (int const*,int,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_expand_192(void)
{
  /* This is FIPS-197 appendix A.2. */
  const uint8_t key[] = {
    0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 
    0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b
  };

  const uint32_t answer[] = {
    0x8e73b0f7, 0xda0e6452, 0xc810f32b, 0x809079e5, 0x62f8ead2, 0x522c6b7b,
    0xfe0c91f7, 0x2402f5a5, 0xec12068e, 0x6c827f6b, 0x0e7a95b9, 0x5c56fec2,
    0x4db7b4bd, 0x69b54118, 0x85a74796, 0xe92538fd, 0xe75fad44, 0xbb095386,
    0x485af057, 0x21efb14f, 0xa448f6d9, 0x4d6dce24, 0xaa326360, 0x113b30e6,
    0xa25e7ed5, 0x83b1cf9a, 0x27f93943, 0x6a94f767, 0xc0a69407, 0xd19da4e1,
    0xec1786eb, 0x6fa64971, 0x485f7032, 0x22cb8755, 0xe26d1352, 0x33f0b7b3,
    0x40beeb28, 0x2f18a259, 0x6747d26b, 0x458c553e, 0xa7e1466c, 0x9411f1df,
    0x821f750a, 0xad07d753, 0xca400538, 0x8fcc5006, 0x282d166a, 0xbc3ce7b5,
    0xe98ba06f, 0x448c773c, 0x8ecc7204, 0x01002202
  };

  test_expand(key, sizeof key, answer, ARRAYCOUNT(answer));
}