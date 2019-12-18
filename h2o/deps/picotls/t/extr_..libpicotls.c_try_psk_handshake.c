#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verify_data ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_37__ {size_t count; struct st_ptls_client_hello_psk_t* list; } ;
struct TYPE_38__ {TYPE_4__ identities; scalar_t__ early_data_indication; } ;
struct st_ptls_client_hello_t {TYPE_5__ psk; } ;
struct TYPE_36__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct st_ptls_client_hello_psk_t {TYPE_3__ binder; scalar_t__ obfuscated_ticket_age; int /*<<< orphan*/  identity; } ;
struct TYPE_41__ {TYPE_21__* key_schedule; TYPE_9__* key_share; int /*<<< orphan*/ * negotiated_protocol; TYPE_2__* cipher_suite; TYPE_1__* ctx; int /*<<< orphan*/ * server_name; } ;
typedef  TYPE_8__ ptls_t ;
struct TYPE_42__ {scalar_t__ id; } ;
typedef  TYPE_9__ ptls_key_exchange_algorithm_t ;
struct TYPE_29__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_10__ ptls_iovec_t ;
struct TYPE_30__ {scalar_t__ off; scalar_t__ base; } ;
typedef  TYPE_11__ ptls_buffer_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  decbuf_small ;
typedef  int /*<<< orphan*/  binder_key ;
struct TYPE_40__ {TYPE_6__* algo; } ;
struct TYPE_39__ {scalar_t__ digest_size; } ;
struct TYPE_35__ {scalar_t__ id; } ;
struct TYPE_34__ {TYPE_7__* hashes; } ;
struct TYPE_33__ {TYPE_9__** key_exchanges; scalar_t__ ticket_lifetime; TYPE_15__* encrypt_ticket; TYPE_18__* get_time; } ;
struct TYPE_32__ {scalar_t__ (* cb ) (TYPE_18__*) ;} ;
struct TYPE_31__ {int (* cb ) (TYPE_15__*,TYPE_8__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int PTLS_ALERT_DECRYPT_ERROR ; 
 scalar_t__ PTLS_EARLY_DATA_MAX_DELAY ; 
#define  PTLS_ERROR_REJECT_EARLY_DATA 128 
 int PTLS_MAX_DIGEST_SIZE ; 
 size_t SIZE_MAX ; 
 int calc_verify_data (int /*<<< orphan*/ *,TYPE_21__*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_session_identifier (scalar_t__*,TYPE_10__*,scalar_t__*,TYPE_10__*,scalar_t__*,scalar_t__*,TYPE_10__*,scalar_t__,scalar_t__) ; 
 int derive_secret (TYPE_21__*,int /*<<< orphan*/ *,char*) ; 
 int key_schedule_extract (TYPE_21__*,TYPE_10__) ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (TYPE_21__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_11__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_11__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_mem_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_18__*) ; 
 int stub2 (TYPE_15__*,TYPE_8__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_is_string (TYPE_10__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_psk_handshake(ptls_t *tls, size_t *psk_index, int *accept_early_data, struct st_ptls_client_hello_t *ch,
                             ptls_iovec_t ch_trunc)
{
    ptls_buffer_t decbuf;
    ptls_iovec_t ticket_psk, ticket_server_name, ticket_negotiated_protocol;
    uint64_t issue_at, now = tls->ctx->get_time->cb(tls->ctx->get_time);
    uint32_t age_add;
    uint16_t ticket_key_exchange_id, ticket_csid;
    uint8_t decbuf_small[256], binder_key[PTLS_MAX_DIGEST_SIZE], verify_data[PTLS_MAX_DIGEST_SIZE];
    int ret;

    ptls_buffer_init(&decbuf, decbuf_small, sizeof(decbuf_small));

    for (*psk_index = 0; *psk_index < ch->psk.identities.count; ++*psk_index) {
        struct st_ptls_client_hello_psk_t *identity = ch->psk.identities.list + *psk_index;
        /* decrypt and decode */
        int can_accept_early_data = 1;
        decbuf.off = 0;
        switch (tls->ctx->encrypt_ticket->cb(tls->ctx->encrypt_ticket, tls, 0, &decbuf, identity->identity)) {
        case 0: /* decrypted */
            break;
        case PTLS_ERROR_REJECT_EARLY_DATA: /* decrypted, but early data is rejected */
            can_accept_early_data = 0;
            break;
        default: /* decryption failure */
            continue;
        }
        if (decode_session_identifier(&issue_at, &ticket_psk, &age_add, &ticket_server_name, &ticket_key_exchange_id, &ticket_csid,
                                      &ticket_negotiated_protocol, decbuf.base, decbuf.base + decbuf.off) != 0)
            continue;
        /* check age */
        if (now < issue_at)
            continue;
        if (now - issue_at > (uint64_t)tls->ctx->ticket_lifetime * 1000)
            continue;
        *accept_early_data = 0;
        if (ch->psk.early_data_indication && can_accept_early_data) {
            /* accept early-data if abs(diff) between the reported age and the actual age is within += 10 seconds */
            int64_t delta = (now - issue_at) - (identity->obfuscated_ticket_age - age_add);
            if (delta < 0)
                delta = -delta;
            if (delta <= PTLS_EARLY_DATA_MAX_DELAY)
                *accept_early_data = 1;
        }
        /* check server-name */
        if (ticket_server_name.len != 0) {
            if (tls->server_name == NULL)
                continue;
            if (!vec_is_string(ticket_server_name, tls->server_name))
                continue;
        } else {
            if (tls->server_name != NULL)
                continue;
        }
        { /* check key-exchange */
            ptls_key_exchange_algorithm_t **a;
            for (a = tls->ctx->key_exchanges; *a != NULL && (*a)->id != ticket_key_exchange_id; ++a)
                ;
            if (*a == NULL)
                continue;
            tls->key_share = *a;
        }
        /* check cipher-suite */
        if (ticket_csid != tls->cipher_suite->id)
            continue;
        /* check negotiated-protocol */
        if (ticket_negotiated_protocol.len != 0) {
            if (tls->negotiated_protocol == NULL)
                continue;
            if (!vec_is_string(ticket_negotiated_protocol, tls->negotiated_protocol))
                continue;
        }
        /* check the length of the decrypted psk and the PSK binder */
        if (ticket_psk.len != tls->key_schedule->hashes[0].algo->digest_size)
            continue;
        if (ch->psk.identities.list[*psk_index].binder.len != tls->key_schedule->hashes[0].algo->digest_size)
            continue;

        /* found */
        goto Found;
    }

    /* not found */
    *psk_index = SIZE_MAX;
    *accept_early_data = 0;
    tls->key_share = NULL;
    ret = 0;
    goto Exit;

Found:
    if ((ret = key_schedule_extract(tls->key_schedule, ticket_psk)) != 0)
        goto Exit;
    if ((ret = derive_secret(tls->key_schedule, binder_key, "res binder")) != 0)
        goto Exit;
    ptls__key_schedule_update_hash(tls->key_schedule, ch_trunc.base, ch_trunc.len);
    if ((ret = calc_verify_data(verify_data, tls->key_schedule, binder_key)) != 0)
        goto Exit;
    if (!ptls_mem_equal(ch->psk.identities.list[*psk_index].binder.base, verify_data,
                        tls->key_schedule->hashes[0].algo->digest_size)) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    ret = 0;

Exit:
    ptls_buffer_dispose(&decbuf);
    ptls_clear_memory(binder_key, sizeof(binder_key));
    ptls_clear_memory(verify_data, sizeof(verify_data));
    return ret;
}