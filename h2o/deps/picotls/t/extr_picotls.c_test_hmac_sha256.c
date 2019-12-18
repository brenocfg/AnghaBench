#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* final ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ptls_hash_context_t ;
typedef  int /*<<< orphan*/  digest ;
struct TYPE_11__ {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 ; 
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_FREE ; 
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_RESET ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_9__* find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 TYPE_1__* ptls_hmac_create (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_hmac_sha256(void)
{
    /* test vector from RFC 4231 */
    const char *secret = "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b", *message = "Hi There",
               *expected =
                   "\xb0\x34\x4c\x61\xd8\xdb\x38\x53\x5c\xa8\xaf\xce\xaf\x0b\xf1\x2b\x88\x1d\xc2\x00\xc9\x83\x3d\xa7\x26\xe9\x37"
                   "\x6c\x2e\x32\xcf\xf7";
    uint8_t digest[32];

    ptls_hash_context_t *hctx =
        ptls_hmac_create(find_cipher(ctx, PTLS_CIPHER_SUITE_AES_128_GCM_SHA256)->hash, secret, strlen(secret));

    memset(digest, 0, sizeof(digest));
    hctx->update(hctx, message, strlen(message));
    hctx->final(hctx, digest, PTLS_HASH_FINAL_MODE_RESET);
    ok(memcmp(digest, expected, 32) == 0);

    memset(digest, 0, sizeof(digest));
    hctx->update(hctx, message, strlen(message));
    hctx->final(hctx, digest, PTLS_HASH_FINAL_MODE_RESET);
    ok(memcmp(digest, expected, 32) == 0);

    memset(digest, 0, sizeof(digest));
    hctx->update(hctx, message, strlen(message));
    hctx->final(hctx, digest, PTLS_HASH_FINAL_MODE_FREE);
    ok(memcmp(digest, expected, 32) == 0);
}