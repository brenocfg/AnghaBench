#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct st_quicly_cipher_context_t {int dummy; } ;
typedef  int /*<<< orphan*/  secret ;
typedef  int /*<<< orphan*/  salt ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
struct TYPE_4__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ ptls_cipher_suite_t ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  ptls_clear_memory (int*,int) ; 
 int ptls_hkdf_extract (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_iovec_init (int const*,int) ; 
 int setup_initial_key (struct st_quicly_cipher_context_t*,TYPE_1__*,int*,char const*,int) ; 

__attribute__((used)) static int setup_initial_encryption(ptls_cipher_suite_t *cs, struct st_quicly_cipher_context_t *ingress,
                                    struct st_quicly_cipher_context_t *egress, ptls_iovec_t cid, int is_client)
{
    static const uint8_t salt[] = {0xc3, 0xee, 0xf7, 0x12, 0xc7, 0x2e, 0xbb, 0x5a, 0x11, 0xa7,
                                   0xd2, 0x43, 0x2b, 0xb4, 0x63, 0x65, 0xbe, 0xf9, 0xf5, 0x02};
    static const char *labels[2] = {"client in", "server in"};
    uint8_t secret[PTLS_MAX_DIGEST_SIZE];
    int ret;

    /* extract master secret */
    if ((ret = ptls_hkdf_extract(cs->hash, secret, ptls_iovec_init(salt, sizeof(salt)), cid)) != 0)
        goto Exit;

    /* create aead contexts */
    if ((ret = setup_initial_key(ingress, cs, secret, labels[is_client], 0)) != 0)
        goto Exit;
    if ((ret = setup_initial_key(egress, cs, secret, labels[!is_client], 1)) != 0)
        goto Exit;

Exit:
    ptls_clear_memory(secret, sizeof(secret));
    return ret;
}