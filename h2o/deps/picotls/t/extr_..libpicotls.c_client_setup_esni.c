#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ ptls_iovec_t ;
struct TYPE_19__ {int /*<<< orphan*/  pubkey; TYPE_5__* key_share; int /*<<< orphan*/  record_digest; TYPE_9__* cipher; int /*<<< orphan*/  padded_length; } ;
struct TYPE_21__ {TYPE_1__ client; int /*<<< orphan*/  esni_contents_hash; int /*<<< orphan*/  secret; int /*<<< orphan*/  nonce; int /*<<< orphan*/  version; } ;
typedef  TYPE_3__ ptls_esni_secret_t ;
struct TYPE_22__ {int /*<<< orphan*/  (* random_bytes ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_4__ ptls_context_t ;
struct TYPE_24__ {int /*<<< orphan*/  hash; } ;
struct TYPE_23__ {int (* exchange ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__) ;int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int build_esni_contents_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  free_esni_secret (TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_esni_keys (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__**,TYPE_9__**,TYPE_2__*,int /*<<< orphan*/ *,char**,TYPE_2__) ; 
 int ptls_calc_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__) ; 

__attribute__((used)) static int client_setup_esni(ptls_context_t *ctx, ptls_esni_secret_t **esni, ptls_iovec_t esni_keys, char **published_sni,
                             const uint8_t *client_random)
{
    ptls_iovec_t peer_key;
    int ret;

    if ((*esni = malloc(sizeof(**esni))) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    memset(*esni, 0, sizeof(**esni));

    /* parse ESNI_Keys (and return success while keeping *esni NULL) */
    if (parse_esni_keys(ctx, &(*esni)->version, &(*esni)->client.key_share, &(*esni)->client.cipher, &peer_key,
                        &(*esni)->client.padded_length, published_sni, esni_keys) != 0) {
        free(*esni);
        *esni = NULL;
        return 0;
    }

    ctx->random_bytes((*esni)->nonce, sizeof((*esni)->nonce));

    /* calc record digest */
    if ((ret = ptls_calc_hash((*esni)->client.cipher->hash, (*esni)->client.record_digest, esni_keys.base, esni_keys.len)) != 0)
        goto Exit;
    /* derive ECDH secret */
    if ((ret = (*esni)->client.key_share->exchange((*esni)->client.key_share, &(*esni)->client.pubkey, &(*esni)->secret,
                                                   peer_key)) != 0)
        goto Exit;
    /* calc H(ESNIContents) */
    if ((ret = build_esni_contents_hash((*esni)->client.cipher->hash, (*esni)->esni_contents_hash, (*esni)->client.record_digest,
                                        (*esni)->client.key_share->id, (*esni)->client.pubkey, client_random)) != 0)
        goto Exit;

    ret = 0;
Exit:
    if (ret != 0)
        free_esni_secret(esni, 0);
    return ret;
}