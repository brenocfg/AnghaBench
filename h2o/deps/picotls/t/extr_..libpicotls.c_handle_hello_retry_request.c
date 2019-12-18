#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ selected_group; int /*<<< orphan*/  cookie; } ;
struct st_ptls_server_hello_t {TYPE_5__ retry_request; } ;
struct TYPE_15__ {scalar_t__ using_early_data; TYPE_9__* key_share_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_14__ {TYPE_1__ enc; } ;
struct TYPE_18__ {int /*<<< orphan*/  key_schedule; TYPE_7__* key_share; TYPE_4__* ctx; TYPE_3__ client; TYPE_2__ traffic_protection; } ;
typedef  TYPE_6__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_19__ {scalar_t__ id; } ;
typedef  TYPE_7__ ptls_key_exchange_algorithm_t ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_8__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
struct TYPE_21__ {int /*<<< orphan*/  (* on_exchange ) (TYPE_9__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {TYPE_7__** key_exchanges; int /*<<< orphan*/ * update_traffic_key; } ;

/* Variables and functions */
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_schedule_transform_post_ch1hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int send_client_hello (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_hello_retry_request(ptls_t *tls, ptls_message_emitter_t *emitter, struct st_ptls_server_hello_t *sh,
                                      ptls_iovec_t message, ptls_handshake_properties_t *properties)
{
    int ret;

    if (tls->client.key_share_ctx != NULL) {
        tls->client.key_share_ctx->on_exchange(&tls->client.key_share_ctx, 1, NULL, ptls_iovec_init(NULL, 0));
        tls->client.key_share_ctx = NULL;
    }
    if (tls->client.using_early_data) {
        /* release traffic encryption key so that 2nd CH goes out in cleartext, but keep the epoch at 1 since we've already
         * called derive-secret */
        if (tls->ctx->update_traffic_key == NULL) {
            assert(tls->traffic_protection.enc.aead != NULL);
            ptls_aead_free(tls->traffic_protection.enc.aead);
            tls->traffic_protection.enc.aead = NULL;
        }
        tls->client.using_early_data = 0;
    }

    if (sh->retry_request.selected_group != UINT16_MAX) {
        /* we offer the first key_exchanges[0] as KEY_SHARE unless client.negotiate_before_key_exchange is set */
        ptls_key_exchange_algorithm_t **cand;
        for (cand = tls->ctx->key_exchanges; *cand != NULL; ++cand)
            if ((*cand)->id == sh->retry_request.selected_group)
                break;
        if (*cand == NULL) {
            ret = PTLS_ALERT_ILLEGAL_PARAMETER;
            goto Exit;
        }
        tls->key_share = *cand;
    } else if (tls->key_share != NULL) {
        /* retain the key-share using in first CH, if server does not specify one */
    } else {
        ret = PTLS_ALERT_ILLEGAL_PARAMETER;
        goto Exit;
    }

    key_schedule_transform_post_ch1hash(tls->key_schedule);
    ptls__key_schedule_update_hash(tls->key_schedule, message.base, message.len);
    ret = send_client_hello(tls, emitter, properties, &sh->retry_request.cookie);

Exit:
    return ret;
}