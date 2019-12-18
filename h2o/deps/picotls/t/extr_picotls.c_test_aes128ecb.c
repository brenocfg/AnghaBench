#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  expected ;
struct TYPE_4__ {TYPE_1__* aead; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecb_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_2__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ecb (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static void test_aes128ecb(void)
{
    static const uint8_t expected[] = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
                                       0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A};

    test_ecb(find_cipher(ctx, PTLS_CIPHER_SUITE_AES_128_GCM_SHA256)->aead->ecb_cipher, expected, sizeof(expected));
}