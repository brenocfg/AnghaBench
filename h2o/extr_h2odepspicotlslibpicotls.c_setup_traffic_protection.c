#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct st_ptls_traffic_protection_t {size_t epoch; TYPE_11__* aead; scalar_t__* secret; scalar_t__ seq; } ;
struct TYPE_17__ {struct st_ptls_traffic_protection_t dec; struct st_ptls_traffic_protection_t enc; } ;
struct TYPE_22__ {TYPE_14__* key_schedule; TYPE_3__* ctx; TYPE_2__* cipher_suite; TYPE_1__ traffic_protection; } ;
typedef  TYPE_6__ ptls_t ;
struct TYPE_23__ {int (* cb ) (TYPE_7__*,TYPE_6__*,int,size_t,scalar_t__*) ;} ;
struct TYPE_21__ {TYPE_4__* algo; } ;
struct TYPE_20__ {int /*<<< orphan*/  digest_size; } ;
struct TYPE_19__ {int /*<<< orphan*/  hkdf_label_prefix__obsolete; TYPE_7__* update_traffic_key; } ;
struct TYPE_18__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  aead; } ;
struct TYPE_16__ {TYPE_5__* hashes; } ;
struct TYPE_15__ {scalar_t__* static_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_DEBUGF (char*,char const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int derive_secret (TYPE_14__*,scalar_t__*,char const*) ; 
 int /*<<< orphan*/  log_secret (TYPE_6__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_aead_free (TYPE_11__*) ; 
 TYPE_11__* ptls_aead_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_iovec_init (scalar_t__*,int /*<<< orphan*/ ) ; 
 size_t ptls_is_server (TYPE_6__*) ; 
 int stub1 (TYPE_7__*,TYPE_6__*,int,size_t,scalar_t__*) ; 

__attribute__((used)) static int setup_traffic_protection(ptls_t *tls, int is_enc, const char *secret_label, size_t epoch, int skip_notify)
{
    static const char *log_labels[2][4] = {
        {NULL, "CLIENT_EARLY_TRAFFIC_SECRET", "CLIENT_HANDSHAKE_TRAFFIC_SECRET", "CLIENT_TRAFFIC_SECRET_0"},
        {NULL, NULL, "SERVER_HANDSHAKE_TRAFFIC_SECRET", "SERVER_TRAFFIC_SECRET_0"}};
    struct st_ptls_traffic_protection_t *ctx = is_enc ? &tls->traffic_protection.enc : &tls->traffic_protection.dec;

    if (secret_label != NULL) {
        int ret;
        if ((ret = derive_secret(tls->key_schedule, ctx->secret, secret_label)) != 0)
            return ret;
    }

    ctx->epoch = epoch;

    /* special path for applications having their own record layer */
    if (tls->ctx->update_traffic_key != NULL) {
        if (skip_notify)
            return 0;
        return tls->ctx->update_traffic_key->cb(tls->ctx->update_traffic_key, tls, is_enc, epoch, ctx->secret);
    }

    if (ctx->aead != NULL)
        ptls_aead_free(ctx->aead);
    if ((ctx->aead = ptls_aead_new(tls->cipher_suite->aead, tls->cipher_suite->hash, is_enc, ctx->secret,
                                   tls->ctx->hkdf_label_prefix__obsolete)) == NULL)
        return PTLS_ERROR_NO_MEMORY; /* TODO obtain error from ptls_aead_new */
    ctx->seq = 0;

    log_secret(tls, log_labels[ptls_is_server(tls) == is_enc][epoch],
               ptls_iovec_init(ctx->secret, tls->key_schedule->hashes[0].algo->digest_size));
    PTLS_DEBUGF("[%s] %02x%02x,%02x%02x\n", log_labels[ptls_is_server(tls)][epoch], (unsigned)ctx->secret[0],
                (unsigned)ctx->secret[1], (unsigned)ctx->aead->static_iv[0], (unsigned)ctx->aead->static_iv[1]);

    return 0;
}