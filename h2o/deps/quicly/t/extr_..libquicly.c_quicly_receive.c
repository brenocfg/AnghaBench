#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_105__   TYPE_9__ ;
typedef  struct TYPE_104__   TYPE_8__ ;
typedef  struct TYPE_103__   TYPE_7__ ;
typedef  struct TYPE_102__   TYPE_6__ ;
typedef  struct TYPE_101__   TYPE_5__ ;
typedef  struct TYPE_100__   TYPE_4__ ;
typedef  struct TYPE_99__   TYPE_44__ ;
typedef  struct TYPE_98__   TYPE_42__ ;
typedef  struct TYPE_97__   TYPE_3__ ;
typedef  struct TYPE_96__   TYPE_39__ ;
typedef  struct TYPE_95__   TYPE_35__ ;
typedef  struct TYPE_94__   TYPE_34__ ;
typedef  struct TYPE_93__   TYPE_33__ ;
typedef  struct TYPE_92__   TYPE_32__ ;
typedef  struct TYPE_91__   TYPE_31__ ;
typedef  struct TYPE_90__   TYPE_30__ ;
typedef  struct TYPE_89__   TYPE_2__ ;
typedef  struct TYPE_88__   TYPE_29__ ;
typedef  struct TYPE_87__   TYPE_28__ ;
typedef  struct TYPE_86__   TYPE_27__ ;
typedef  struct TYPE_85__   TYPE_26__ ;
typedef  struct TYPE_84__   TYPE_25__ ;
typedef  struct TYPE_83__   TYPE_24__ ;
typedef  struct TYPE_82__   TYPE_23__ ;
typedef  struct TYPE_81__   TYPE_22__ ;
typedef  struct TYPE_80__   TYPE_21__ ;
typedef  struct TYPE_79__   TYPE_20__ ;
typedef  struct TYPE_78__   TYPE_1__ ;
typedef  struct TYPE_77__   TYPE_19__ ;
typedef  struct TYPE_76__   TYPE_18__ ;
typedef  struct TYPE_75__   TYPE_17__ ;
typedef  struct TYPE_74__   TYPE_16__ ;
typedef  struct TYPE_73__   TYPE_15__ ;
typedef  struct TYPE_72__   TYPE_14__ ;
typedef  struct TYPE_71__   TYPE_13__ ;
typedef  struct TYPE_70__   TYPE_12__ ;
typedef  struct TYPE_69__   TYPE_11__ ;
typedef  struct TYPE_68__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct st_quicly_pn_space_t {int /*<<< orphan*/  next_expected_packet_number; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct TYPE_80__ {int /*<<< orphan*/  size; } ;
struct TYPE_81__ {TYPE_21__ vecs; } ;
struct TYPE_91__ {TYPE_22__ egress; } ;
typedef  TYPE_31__ quicly_streambuf_t ;
struct TYPE_92__ {TYPE_31__* data; } ;
typedef  TYPE_32__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
struct TYPE_73__ {int* base; scalar_t__ len; } ;
struct TYPE_95__ {int* base; scalar_t__ len; } ;
struct TYPE_78__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_89__ {TYPE_1__ encrypted; } ;
struct TYPE_101__ {TYPE_35__ src; TYPE_2__ dest; } ;
struct TYPE_100__ {scalar_t__ len; int* base; } ;
struct TYPE_93__ {scalar_t__ version; TYPE_15__ octets; TYPE_5__ cid; TYPE_4__ token; int /*<<< orphan*/  encrypted_off; } ;
typedef  TYPE_33__ quicly_decoded_packet_t ;
struct TYPE_88__ {int /*<<< orphan*/  alarm_at; } ;
struct TYPE_90__ {TYPE_29__ loss; int /*<<< orphan*/  send_ack_at; int /*<<< orphan*/  packet_number; int /*<<< orphan*/  sentmap; } ;
struct TYPE_82__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_99__ {TYPE_23__ sa; } ;
struct TYPE_86__ {TYPE_44__ address; } ;
struct TYPE_84__ {int /*<<< orphan*/  disable_active_migration; } ;
struct TYPE_74__ {int validated; } ;
struct TYPE_98__ {int* len; int* cid; } ;
struct TYPE_85__ {TYPE_25__ transport_params; TYPE_16__ address_validation; TYPE_42__ cid; } ;
struct TYPE_71__ {int /*<<< orphan*/  received; } ;
struct TYPE_70__ {int received; } ;
struct TYPE_72__ {TYPE_13__ num_bytes; TYPE_12__ num_packets; } ;
struct TYPE_87__ {int state; TYPE_27__ host; TYPE_26__ peer; TYPE_14__ stats; int /*<<< orphan*/  ctx; } ;
struct TYPE_83__ {int handshake_scheduled_for_discard; int /*<<< orphan*/  tls; } ;
struct TYPE_97__ {int* base; scalar_t__ len; } ;
struct TYPE_94__ {TYPE_30__ egress; TYPE_28__ super; TYPE_24__ crypto; TYPE_20__* handshake; TYPE_17__* initial; TYPE_11__* application; TYPE_42__ retry_odcid; TYPE_3__ token; } ;
typedef  TYPE_34__ quicly_conn_t ;
typedef  TYPE_35__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
struct TYPE_104__ {int /*<<< orphan*/ * one_rtt; int /*<<< orphan*/ * zero_rtt; } ;
struct TYPE_105__ {int /*<<< orphan*/ ** aead; TYPE_8__ header_protection; } ;
struct TYPE_103__ {int /*<<< orphan*/ * aead; int /*<<< orphan*/ * header_protection; } ;
struct TYPE_96__ {int /*<<< orphan*/ * aead; int /*<<< orphan*/ * header_protection; } ;
struct TYPE_102__ {TYPE_39__ ingress; TYPE_39__ egress; } ;
struct TYPE_76__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_77__ {TYPE_18__ egress; TYPE_7__ ingress; } ;
struct TYPE_79__ {TYPE_19__ cipher; } ;
struct TYPE_75__ {TYPE_6__ cipher; } ;
struct TYPE_68__ {TYPE_9__ ingress; } ;
struct TYPE_69__ {TYPE_10__ cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  CRYPTO_DECRYPT ; 
 int PTLS_ERROR_NO_MEMORY ; 
 size_t QUICLY_EPOCH_0RTT ; 
#define  QUICLY_EPOCH_1RTT 137 
#define  QUICLY_EPOCH_HANDSHAKE 136 
#define  QUICLY_EPOCH_INITIAL 135 
#define  QUICLY_ERROR_PACKET_IGNORED 134 
 int /*<<< orphan*/  QUICLY_FRAME_TYPE_PADDING ; 
 scalar_t__ QUICLY_MAX_TOKEN_LEN ; 
 scalar_t__ QUICLY_PACKET_IS_LONG_HEADER (int) ; 
#define  QUICLY_PACKET_TYPE_0RTT 133 
 int QUICLY_PACKET_TYPE_BITMASK ; 
#define  QUICLY_PACKET_TYPE_HANDSHAKE 132 
#define  QUICLY_PACKET_TYPE_INITIAL 131 
#define  QUICLY_PACKET_TYPE_RETRY 130 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_34__*,int /*<<< orphan*/ ,int*,...) ; 
 int /*<<< orphan*/  QUICLY_PROBE_HEXDUMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  QUICLY_STATE_CLOSING 129 
 int QUICLY_STATE_CONNECTED ; 
#define  QUICLY_STATE_DRAINING 128 
 int QUICLY_STATE_FIRSTFLIGHT ; 
 int QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  QUICTRACE_RECV ; 
 int /*<<< orphan*/  RECEIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_consistency (TYPE_34__*,int /*<<< orphan*/ ) ; 
 TYPE_35__ decrypt_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_33__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_handshake_context ; 
 int discard_initial_context (TYPE_34__*) ; 
 int discard_sentmap_by_epoch (TYPE_34__*,unsigned int) ; 
 int /*<<< orphan*/  dispose_cipher (TYPE_39__*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  get_aes128gcmsha256 (int /*<<< orphan*/ ) ; 
 int handle_payload (TYPE_34__*,size_t,int*,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int handle_stateless_reset (TYPE_34__*) ; 
 int handle_version_negotiation_packet (TYPE_34__*,TYPE_33__*) ; 
 int /*<<< orphan*/  initiate_close (TYPE_34__*,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_stateless_reset (TYPE_34__*,TYPE_33__*) ; 
 int* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  probe_now () ; 
 int /*<<< orphan*/  ptls_handshake_is_complete (int /*<<< orphan*/ ) ; 
 TYPE_35__ ptls_iovec_init (int*,int*) ; 
 int /*<<< orphan*/  quicly_cid_is_equal (TYPE_42__*,TYPE_35__) ; 
 TYPE_32__* quicly_get_stream (TYPE_34__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_is_client (TYPE_34__*) ; 
 int /*<<< orphan*/ * quicly_sentmap_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sentmap_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int quicly_sentmap_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 
 int record_receipt (TYPE_34__*,struct st_quicly_pn_space_t*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  set_address (TYPE_44__*,struct sockaddr*) ; 
 int /*<<< orphan*/  set_cid (TYPE_42__*,TYPE_35__) ; 
 int setup_initial_encryption (int /*<<< orphan*/ ,TYPE_39__*,TYPE_39__*,TYPE_35__,int) ; 
 int /*<<< orphan*/  should_send_max_data (TYPE_34__*) ; 
 int /*<<< orphan*/  update_idle_timeout (TYPE_34__*,int) ; 
 int /*<<< orphan*/  update_loss_alarm (TYPE_34__*) ; 
 int /*<<< orphan*/  update_now (int /*<<< orphan*/ ) ; 

int quicly_receive(quicly_conn_t *conn, struct sockaddr *dest_addr, struct sockaddr *src_addr, quicly_decoded_packet_t *packet)
{
    ptls_cipher_context_t *header_protection;
    ptls_aead_context_t **aead;
    struct st_quicly_pn_space_t **space;
    size_t epoch;
    ptls_iovec_t payload;
    uint64_t pn, offending_frame_type = QUICLY_FRAME_TYPE_PADDING;
    int is_ack_only, ret;

    update_now(conn->super.ctx);

    QUICLY_PROBE(RECEIVE, conn, probe_now(), QUICLY_PROBE_HEXDUMP(packet->cid.dest.encrypted.base, packet->cid.dest.encrypted.len),
                 packet->octets.base, packet->octets.len);

    if (is_stateless_reset(conn, packet)) {
        ret = handle_stateless_reset(conn);
        goto Exit;
    }

    /* FIXME check peer address */

    switch (conn->super.state) {
    case QUICLY_STATE_CLOSING:
        conn->super.state = QUICLY_STATE_DRAINING;
        conn->egress.send_ack_at = 0; /* send CONNECTION_CLOSE */
        ret = 0;
        goto Exit;
    case QUICLY_STATE_DRAINING:
        ret = 0;
        goto Exit;
    default:
        break;
    }

    if (QUICLY_PACKET_IS_LONG_HEADER(packet->octets.base[0])) {
        if (conn->super.state == QUICLY_STATE_FIRSTFLIGHT) {
            if (packet->version == 0)
                return handle_version_negotiation_packet(conn, packet);
        }
        switch (packet->octets.base[0] & QUICLY_PACKET_TYPE_BITMASK) {
        case QUICLY_PACKET_TYPE_RETRY: {
            /* check the packet */
            if (packet->token.len >= QUICLY_MAX_TOKEN_LEN) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            ptls_iovec_t odcid = ptls_iovec_init(packet->octets.base + packet->encrypted_off,
                                                 packet->token.base - (packet->octets.base + packet->encrypted_off));
            if (!quicly_cid_is_equal(&conn->super.peer.cid, odcid)) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            if (quicly_cid_is_equal(&conn->super.peer.cid, packet->cid.src)) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            /* do not accept a second Retry */
            if (conn->retry_odcid.len != 0) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            /* store token and ODCID */
            free(conn->token.base);
            if ((conn->token.base = malloc(packet->token.len)) == NULL) {
                ret = PTLS_ERROR_NO_MEMORY;
                goto Exit;
            }
            memcpy(conn->token.base, packet->token.base, packet->token.len);
            conn->token.len = packet->token.len;
            conn->retry_odcid = conn->super.peer.cid;
            /* update DCID */
            set_cid(&conn->super.peer.cid, packet->cid.src);
            /* replace initial keys */
            dispose_cipher(&conn->initial->cipher.ingress);
            dispose_cipher(&conn->initial->cipher.egress);
            if ((ret = setup_initial_encryption(get_aes128gcmsha256(conn->super.ctx), &conn->initial->cipher.ingress,
                                                &conn->initial->cipher.egress,
                                                ptls_iovec_init(conn->super.peer.cid.cid, conn->super.peer.cid.len), 1)) != 0)
                goto Exit;
            /* schedule retransmit */
            ret = discard_sentmap_by_epoch(conn, ~0u);
            goto Exit;
        } break;
        case QUICLY_PACKET_TYPE_INITIAL:
            if (conn->initial == NULL || (header_protection = conn->initial->cipher.ingress.header_protection) == NULL) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            /* update cid if this is the first Initial packet that's being received */
            if (conn->super.state == QUICLY_STATE_FIRSTFLIGHT) {
                assert(quicly_is_client(conn));
                memcpy(conn->super.peer.cid.cid, packet->cid.src.base, packet->cid.src.len);
                conn->super.peer.cid.len = packet->cid.src.len;
            }
            aead = &conn->initial->cipher.ingress.aead;
            space = (void *)&conn->initial;
            epoch = QUICLY_EPOCH_INITIAL;
            break;
        case QUICLY_PACKET_TYPE_HANDSHAKE:
            if (conn->handshake == NULL || (header_protection = conn->handshake->cipher.ingress.header_protection) == NULL) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            aead = &conn->handshake->cipher.ingress.aead;
            space = (void *)&conn->handshake;
            epoch = QUICLY_EPOCH_HANDSHAKE;
            break;
        case QUICLY_PACKET_TYPE_0RTT:
            if (quicly_is_client(conn)) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            if (conn->application == NULL ||
                (header_protection = conn->application->cipher.ingress.header_protection.zero_rtt) == NULL) {
                ret = QUICLY_ERROR_PACKET_IGNORED;
                goto Exit;
            }
            aead = &conn->application->cipher.ingress.aead[0];
            space = (void *)&conn->application;
            epoch = QUICLY_EPOCH_0RTT;
            break;
        default:
            ret = QUICLY_ERROR_PACKET_IGNORED;
            goto Exit;
        }
    } else {
        /* first 1-RTT keys is key_phase 1, see doc-comment of cipher.ingress */
        if (conn->application == NULL ||
            (header_protection = conn->application->cipher.ingress.header_protection.one_rtt) == NULL) {
            ret = QUICLY_ERROR_PACKET_IGNORED;
            goto Exit;
        }
        aead = conn->application->cipher.ingress.aead;
        space = (void *)&conn->application;
        epoch = QUICLY_EPOCH_1RTT;
    }

    /* decrypt */
    if ((payload = decrypt_packet(header_protection, aead, &(*space)->next_expected_packet_number, packet, &pn)).base == NULL) {
        ret = QUICLY_ERROR_PACKET_IGNORED;
        goto Exit;
    }
    if (payload.len == 0) {
        ret = QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION;
        goto Exit;
    }

    QUICLY_PROBE(CRYPTO_DECRYPT, conn, pn, payload.base, payload.len);
    QUICLY_PROBE(QUICTRACE_RECV, conn, probe_now(), pn);

    /* update states */
    if (conn->super.state == QUICLY_STATE_FIRSTFLIGHT)
        conn->super.state = QUICLY_STATE_CONNECTED;
    conn->super.stats.num_packets.received += 1;
    conn->super.stats.num_bytes.received += packet->octets.len;

    /* state updates, that are triggered by the receipt of a packet */
    if (epoch == QUICLY_EPOCH_HANDSHAKE && conn->initial != NULL) {
        /* Discard Initial space before processing the payload of the Handshake packet to avoid the chance of an ACK frame included
         * in the Handshake packet setting a loss timer for the Initial packet. */
        if ((ret = discard_initial_context(conn)) != 0)
            goto Exit;
        update_loss_alarm(conn);
        conn->super.peer.address_validation.validated = 1;
    }

    /* handle the payload */
    if ((ret = handle_payload(conn, epoch, payload.base, payload.len, &offending_frame_type, &is_ack_only)) != 0)
        goto Exit;
    if (*space != NULL) {
        if ((ret = record_receipt(conn, *space, pn, is_ack_only, epoch)) != 0)
            goto Exit;
    }

    /* state updates post payload processing */
    switch (epoch) {
    case QUICLY_EPOCH_INITIAL:
        assert(conn->initial != NULL);
        if (quicly_is_client(conn) && conn->handshake != NULL && conn->handshake->cipher.egress.aead != NULL) {
            if ((ret = discard_initial_context(conn)) != 0)
                goto Exit;
            update_loss_alarm(conn);
        }
        break;
    case QUICLY_EPOCH_HANDSHAKE:
        /* schedule the timer to discard contexts related to the handshake if we have received all handshake messages and all the
         * messages we sent have been acked */
        if (!conn->crypto.handshake_scheduled_for_discard && ptls_handshake_is_complete(conn->crypto.tls)) {
            quicly_stream_t *stream = quicly_get_stream(conn, -(quicly_stream_id_t)(1 + QUICLY_EPOCH_HANDSHAKE));
            assert(stream != NULL);
            quicly_streambuf_t *buf = stream->data;
            if (buf->egress.vecs.size == 0) {
                if ((ret = quicly_sentmap_prepare(&conn->egress.sentmap, conn->egress.packet_number, now,
                                                  QUICLY_EPOCH_HANDSHAKE)) != 0)
                    goto Exit;
                if (quicly_sentmap_allocate(&conn->egress.sentmap, discard_handshake_context) == NULL) {
                    ret = PTLS_ERROR_NO_MEMORY;
                    goto Exit;
                }
                quicly_sentmap_commit(&conn->egress.sentmap, 0);
                ++conn->egress.packet_number;
                conn->crypto.handshake_scheduled_for_discard = 1;
            }
        }
        /* when running as a client, respect "disable_migration" TP sent by the peer at the end of the TLS handshake */
        if (quicly_is_client(conn) && conn->super.host.address.sa.sa_family == AF_UNSPEC && dest_addr != NULL &&
            dest_addr->sa_family != AF_UNSPEC && ptls_handshake_is_complete(conn->crypto.tls) &&
            conn->super.peer.transport_params.disable_active_migration)
            set_address(&conn->super.host.address, dest_addr);
        break;
    case QUICLY_EPOCH_1RTT:
        if (!is_ack_only && should_send_max_data(conn))
            conn->egress.send_ack_at = 0;
        break;
    default:
        break;
    }

    update_idle_timeout(conn, 1);

Exit:
    switch (ret) {
    case 0:
        /* Avoid time in the past being emitted by quicly_get_first_timeout. We hit the condition below when retransmission is
         * suspended by the 3x limit (in which case we have loss.alarm_at set but return INT64_MAX from quicly_get_first_timeout
         * until we receive something from the client).
         */
        if (conn->egress.loss.alarm_at < now)
            conn->egress.loss.alarm_at = now;
        assert_consistency(conn, 0);
        break;
    case QUICLY_ERROR_PACKET_IGNORED:
        break;
    default: /* close connection */
        initiate_close(conn, ret, offending_frame_type, "");
        ret = 0;
        break;
    }
    return ret;
}