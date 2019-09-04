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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  expected ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_CHACHA20_POLY1305_SHA256 ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ctr (int /*<<< orphan*/ ,int const*,int,int const*,int,int const*,int) ; 

__attribute__((used)) static void test_chacha20(void)
{
    static const uint8_t key[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                                  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
                         iv[] = {1, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0x4a, 0, 0, 0, 0},
                         expected[] = {0x10, 0xf1, 0xe7, 0xe4, 0xd1, 0x3b, 0x59, 0x15, 0x50, 0x0f, 0xdd,
                                       0x1f, 0xa3, 0x20, 0x71, 0xc4, 0xc7, 0xd1, 0xf4, 0xc7, 0x33, 0xc0,
                                       0x68, 0x03, 0x04, 0x22, 0xaa, 0x9a, 0xc3, 0xd4, 0x6c, 0x4e};

    test_ctr(find_cipher(ctx, PTLS_CIPHER_SUITE_CHACHA20_POLY1305_SHA256), key, sizeof(key), iv, sizeof(iv), expected,
             sizeof(expected));
}