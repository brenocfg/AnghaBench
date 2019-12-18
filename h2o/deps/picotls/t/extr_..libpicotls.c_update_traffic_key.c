#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_ptls_traffic_protection_t {int /*<<< orphan*/ * secret; } ;
typedef  int /*<<< orphan*/  secret ;
struct TYPE_9__ {struct st_ptls_traffic_protection_t dec; struct st_ptls_traffic_protection_t enc; } ;
struct TYPE_12__ {TYPE_3__* key_schedule; TYPE_1__ traffic_protection; } ;
typedef  TYPE_4__ ptls_t ;
struct TYPE_13__ {int /*<<< orphan*/  digest_size; } ;
typedef  TYPE_5__ ptls_hash_algorithm_t ;
struct TYPE_11__ {int /*<<< orphan*/  hkdf_label_prefix; TYPE_2__* hashes; } ;
struct TYPE_10__ {TYPE_5__* algo; } ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int hkdf_expand_label (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int setup_traffic_protection (TYPE_4__*,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int update_traffic_key(ptls_t *tls, int is_enc)
{
    struct st_ptls_traffic_protection_t *tp = is_enc ? &tls->traffic_protection.enc : &tls->traffic_protection.dec;
    uint8_t secret[PTLS_MAX_DIGEST_SIZE];
    int ret;

    ptls_hash_algorithm_t *hash = tls->key_schedule->hashes[0].algo;
    if ((ret = hkdf_expand_label(hash, secret, hash->digest_size, ptls_iovec_init(tp->secret, hash->digest_size), "traffic upd",
                                 ptls_iovec_init(NULL, 0), tls->key_schedule->hkdf_label_prefix)) != 0)
        goto Exit;
    memcpy(tp->secret, secret, sizeof(secret));
    ret = setup_traffic_protection(tls, is_enc, NULL, 3, 1);

Exit:
    ptls_clear_memory(secret, sizeof(secret));
    return ret;
}