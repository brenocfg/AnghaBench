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
typedef  int quicly_sentmap_event_t ;
typedef  int /*<<< orphan*/  quicly_sent_t ;
typedef  int /*<<< orphan*/  quicly_sent_packet_t ;
struct TYPE_13__ {TYPE_4__* application; int /*<<< orphan*/  handshake; } ;
typedef  TYPE_5__ quicly_conn_t ;
struct TYPE_9__ {int /*<<< orphan*/ * zero_rtt; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** aead; TYPE_1__ header_protection; } ;
struct TYPE_11__ {TYPE_2__ ingress; } ;
struct TYPE_12__ {TYPE_3__ cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_EPOCH_HANDSHAKE ; 
#define  QUICLY_SENTMAP_EVENT_ACKED 130 
#define  QUICLY_SENTMAP_EVENT_EXPIRED 129 
#define  QUICLY_SENTMAP_EVENT_LOST 128 
 int QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_handshake_flow (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_handshake_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_is_client (TYPE_5__*) ; 

__attribute__((used)) static int discard_handshake_context(quicly_conn_t *conn, const quicly_sent_packet_t *packet, quicly_sent_t *sent,
                                     quicly_sentmap_event_t event)
{
    switch (event) {
    case QUICLY_SENTMAP_EVENT_ACKED:
        return QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION;
    case QUICLY_SENTMAP_EVENT_LOST:
        break;
    case QUICLY_SENTMAP_EVENT_EXPIRED:
        /* discard Handshake */
        destroy_handshake_flow(conn, QUICLY_EPOCH_HANDSHAKE);
        free_handshake_space(&conn->handshake);
        /* discard 0-RTT receive context */
        if (!quicly_is_client(conn) && conn->application->cipher.ingress.header_protection.zero_rtt != NULL) {
            assert(conn->application->cipher.ingress.aead[0] != NULL);
            ptls_cipher_free(conn->application->cipher.ingress.header_protection.zero_rtt);
            conn->application->cipher.ingress.header_protection.zero_rtt = NULL;
            ptls_aead_free(conn->application->cipher.ingress.aead[0]);
            conn->application->cipher.ingress.aead[0] = NULL;
        }
        break;
    }
    return 0;
}