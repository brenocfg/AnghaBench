#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {TYPE_1__* aead; } ;
typedef  TYPE_2__ ptls_cipher_suite_t ;
typedef  int /*<<< orphan*/  expected ;
struct TYPE_4__ {int /*<<< orphan*/  ecb_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_256_GCM_SHA384 ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_2__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ecb (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static void test_aes256ecb(void)
{
    static const uint8_t expected[] = {0x8E, 0xA2, 0xB7, 0xCA, 0x51, 0x67, 0x45, 0xBF,
                                       0xEA, 0xFC, 0x49, 0x90, 0x4B, 0x49, 0x60, 0x89};
    ptls_cipher_suite_t *cipher = find_cipher(ctx, PTLS_CIPHER_SUITE_AES_256_GCM_SHA384);

    if (cipher != NULL)
        test_ecb(cipher->aead->ecb_cipher, expected, sizeof(expected));
}