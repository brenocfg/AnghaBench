#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char const uint8_t ;
typedef  int /*<<< orphan*/  salt ;
struct TYPE_5__ {int digest_size; } ;
typedef  TYPE_1__ ptls_hash_algorithm_t ;
typedef  int /*<<< orphan*/  okm ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  ikm ;
struct TYPE_6__ {TYPE_1__* hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 ; 
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_4__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_hkdf_expand (TYPE_1__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_hkdf_extract (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_iovec_init (char const*,int) ; 

__attribute__((used)) static void test_hkdf(void)
{
    ptls_hash_algorithm_t *sha256 = find_cipher(ctx, PTLS_CIPHER_SUITE_AES_128_GCM_SHA256)->hash;
    const char salt[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c";
    const char ikm[] = "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b";
    const char info[] = "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9";
    uint8_t prk[PTLS_MAX_DIGEST_SIZE];
    uint8_t okm[42];

    ptls_hkdf_extract(sha256, prk, ptls_iovec_init(salt, sizeof(salt) - 1), ptls_iovec_init(ikm, sizeof(ikm) - 1));
    ok(memcmp(prk,
              "\x07\x77\x09\x36\x2c\x2e\x32\xdf\x0d\xdc\x3f\x0d\xc4\x7b\xba\x63\x90\xb6\xc7\x3b\xb5\x0f\x9c\x31\x22\xec\x84"
              "\x4a\xd7\xc2\xb3\xe5",
              32) == 0);

    ptls_hkdf_expand(sha256, okm, sizeof(okm), ptls_iovec_init(prk, sha256->digest_size), ptls_iovec_init(info, sizeof(info) - 1));
    ok(memcmp(okm,
              "\x3c\xb2\x5f\x25\xfa\xac\xd5\x7a\x90\x43\x4f\x64\xd0\x36\x2f\x2a\x2d\x2d\x0a\x90\xcf\x1a\x5a\x4c\x5d\xb0\x2d"
              "\x56\xec\xc4\xc5\xbf\x34\x00\x72\x08\xd5\xb8\x87\x18\x58\x65",
              sizeof(okm)) == 0);
}