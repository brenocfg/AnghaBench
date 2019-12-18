#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  verify_ctx; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_21__ {TYPE_9__* base; } ;
struct TYPE_22__ {TYPE_5__ context; } ;
struct TYPE_23__ {TYPE_6__ certificate_request; TYPE_10__* key_share_ctx; } ;
struct TYPE_19__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_18__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_20__ {TYPE_3__ enc; TYPE_2__ dec; } ;
struct TYPE_17__ {int /*<<< orphan*/  mess; int /*<<< orphan*/  rec; } ;
struct TYPE_25__ {int /*<<< orphan*/  ctx; struct TYPE_25__* pending_handshake_secret; TYPE_8__ certificate_verify; TYPE_7__ client; scalar_t__ is_server; struct TYPE_25__* negotiated_protocol; struct TYPE_25__* server_name; TYPE_4__ traffic_protection; int /*<<< orphan*/ * key_schedule; int /*<<< orphan*/ * esni; TYPE_1__ recvbuf; } ;
typedef  TYPE_9__ ptls_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* on_exchange ) (TYPE_10__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  PTLS_PROBE0 (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  free (TYPE_9__*) ; 
 int /*<<< orphan*/  free_esni_secret (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  free_exporter_master_secret (TYPE_9__*,int) ; 
 int /*<<< orphan*/  key_schedule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_clear_memory (TYPE_9__*,int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_open_count (int /*<<< orphan*/ ,int) ; 

void ptls_free(ptls_t *tls)
{
    PTLS_PROBE0(FREE, tls);
    ptls_buffer_dispose(&tls->recvbuf.rec);
    ptls_buffer_dispose(&tls->recvbuf.mess);
    free_exporter_master_secret(tls, 1);
    free_exporter_master_secret(tls, 0);
    if (tls->esni != NULL)
        free_esni_secret(&tls->esni, tls->is_server);
    if (tls->key_schedule != NULL)
        key_schedule_free(tls->key_schedule);
    if (tls->traffic_protection.dec.aead != NULL)
        ptls_aead_free(tls->traffic_protection.dec.aead);
    if (tls->traffic_protection.enc.aead != NULL)
        ptls_aead_free(tls->traffic_protection.enc.aead);
    free(tls->server_name);
    free(tls->negotiated_protocol);
    if (tls->is_server) {
        /* nothing to do */
    } else {
        if (tls->client.key_share_ctx != NULL)
            tls->client.key_share_ctx->on_exchange(&tls->client.key_share_ctx, 1, NULL, ptls_iovec_init(NULL, 0));
        if (tls->client.certificate_request.context.base != NULL)
            free(tls->client.certificate_request.context.base);
    }
    if (tls->certificate_verify.cb != NULL) {
        tls->certificate_verify.cb(tls->certificate_verify.verify_ctx, ptls_iovec_init(NULL, 0), ptls_iovec_init(NULL, 0));
    }
    if (tls->pending_handshake_secret != NULL) {
        ptls_clear_memory(tls->pending_handshake_secret, PTLS_MAX_DIGEST_SIZE);
        free(tls->pending_handshake_secret);
    }
    update_open_count(tls->ctx, -1);
    ptls_clear_memory(tls, sizeof(*tls));
    free(tls);
}