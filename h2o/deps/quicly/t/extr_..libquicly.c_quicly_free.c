#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {struct st_quicly_pending_path_challenge_t* base; } ;
struct TYPE_15__ {int /*<<< orphan*/  buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  tls; TYPE_11__ transport_params; } ;
struct TYPE_26__ {int /*<<< orphan*/  blocked; int /*<<< orphan*/  active; } ;
struct TYPE_14__ {TYPE_9__ _default_scheduler; } ;
struct TYPE_23__ {int /*<<< orphan*/  bidi; int /*<<< orphan*/  uni; } ;
struct TYPE_24__ {int /*<<< orphan*/  control; TYPE_6__ blocked; } ;
struct TYPE_25__ {TYPE_7__ streams; } ;
struct TYPE_21__ {struct st_quicly_pending_path_challenge_t* head; } ;
struct TYPE_22__ {int /*<<< orphan*/  sentmap; TYPE_4__ path_challenge; } ;
struct TYPE_19__ {int /*<<< orphan*/ * bidi; int /*<<< orphan*/ * uni; } ;
struct TYPE_18__ {int /*<<< orphan*/  sender; } ;
struct TYPE_20__ {TYPE_2__ max_streams; TYPE_1__ max_data; } ;
struct st_quicly_pending_path_challenge_t {TYPE_13__ token; TYPE_12__ crypto; int /*<<< orphan*/  application; int /*<<< orphan*/  handshake; int /*<<< orphan*/  initial; TYPE_10__ super; TYPE_8__ pending; int /*<<< orphan*/  streams; TYPE_5__ egress; struct st_quicly_pending_path_challenge_t* next; TYPE_3__ ingress; } ;
typedef  struct st_quicly_pending_path_challenge_t quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,struct st_quicly_pending_path_challenge_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroy_all_streams (struct st_quicly_pending_path_challenge_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct st_quicly_pending_path_challenge_t*) ; 
 int /*<<< orphan*/  free_application_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_handshake_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_now () ; 
 int /*<<< orphan*/  ptls_buffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_stream_t ; 

void quicly_free(quicly_conn_t *conn)
{
    QUICLY_PROBE(FREE, conn, probe_now());

    destroy_all_streams(conn, 0, 1);

    quicly_maxsender_dispose(&conn->ingress.max_data.sender);
    if (conn->ingress.max_streams.uni != NULL)
        quicly_maxsender_dispose(conn->ingress.max_streams.uni);
    if (conn->ingress.max_streams.bidi != NULL)
        quicly_maxsender_dispose(conn->ingress.max_streams.bidi);
    while (conn->egress.path_challenge.head != NULL) {
        struct st_quicly_pending_path_challenge_t *pending = conn->egress.path_challenge.head;
        conn->egress.path_challenge.head = pending->next;
        free(pending);
    }
    quicly_sentmap_dispose(&conn->egress.sentmap);

    kh_destroy(quicly_stream_t, conn->streams);

    assert(!quicly_linklist_is_linked(&conn->pending.streams.blocked.uni));
    assert(!quicly_linklist_is_linked(&conn->pending.streams.blocked.bidi));
    assert(!quicly_linklist_is_linked(&conn->pending.streams.control));
    assert(!quicly_linklist_is_linked(&conn->super._default_scheduler.active));
    assert(!quicly_linklist_is_linked(&conn->super._default_scheduler.blocked));

    free_handshake_space(&conn->initial);
    free_handshake_space(&conn->handshake);
    free_application_space(&conn->application);

    ptls_buffer_dispose(&conn->crypto.transport_params.buf);
    ptls_free(conn->crypto.tls);

    free(conn->token.base);
    free(conn);
}