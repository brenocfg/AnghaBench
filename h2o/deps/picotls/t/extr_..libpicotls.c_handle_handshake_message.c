#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint8_t ;
struct TYPE_36__ {int state; TYPE_1__* ctx; } ;
typedef  TYPE_2__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_37__ {int* base; int len; } ;
typedef  TYPE_3__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
struct TYPE_35__ {int /*<<< orphan*/  omit_end_of_early_data; } ;

/* Variables and functions */
 int PTLS_ALERT_HANDSHAKE_FAILURE ; 
 int PTLS_ALERT_UNEXPECTED_MESSAGE ; 
 int PTLS_HANDSHAKE_HEADER_SIZE ; 
#define  PTLS_HANDSHAKE_TYPE_CERTIFICATE 146 
 int const PTLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST ; 
 int const PTLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY ; 
 int const PTLS_HANDSHAKE_TYPE_CLIENT_HELLO ; 
#define  PTLS_HANDSHAKE_TYPE_COMPRESSED_CERTIFICATE 145 
 int const PTLS_HANDSHAKE_TYPE_ENCRYPTED_EXTENSIONS ; 
 int const PTLS_HANDSHAKE_TYPE_END_OF_EARLY_DATA ; 
 int const PTLS_HANDSHAKE_TYPE_FINISHED ; 
#define  PTLS_HANDSHAKE_TYPE_KEY_UPDATE 144 
#define  PTLS_HANDSHAKE_TYPE_NEW_SESSION_TICKET 143 
 int const PTLS_HANDSHAKE_TYPE_SERVER_HELLO ; 
 int /*<<< orphan*/  PTLS_PROBE (int /*<<< orphan*/ ,TYPE_2__*,int,int*,int,int) ; 
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE 142 
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_REQUEST_OR_CERTIFICATE 141 
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY 140 
#define  PTLS_STATE_CLIENT_EXPECT_ENCRYPTED_EXTENSIONS 139 
#define  PTLS_STATE_CLIENT_EXPECT_FINISHED 138 
#define  PTLS_STATE_CLIENT_EXPECT_SECOND_SERVER_HELLO 137 
#define  PTLS_STATE_CLIENT_EXPECT_SERVER_HELLO 136 
#define  PTLS_STATE_CLIENT_POST_HANDSHAKE 135 
#define  PTLS_STATE_SERVER_EXPECT_CERTIFICATE 134 
#define  PTLS_STATE_SERVER_EXPECT_CERTIFICATE_VERIFY 133 
#define  PTLS_STATE_SERVER_EXPECT_CLIENT_HELLO 132 
#define  PTLS_STATE_SERVER_EXPECT_END_OF_EARLY_DATA 131 
#define  PTLS_STATE_SERVER_EXPECT_FINISHED 130 
#define  PTLS_STATE_SERVER_EXPECT_SECOND_CLIENT_HELLO 129 
#define  PTLS_STATE_SERVER_POST_HANDSHAKE 128 
 int /*<<< orphan*/  RECEIVE_MESSAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int client_handle_certificate (TYPE_2__*,TYPE_3__) ; 
 int client_handle_certificate_request (TYPE_2__*,TYPE_3__,int /*<<< orphan*/ *) ; 
 int client_handle_certificate_verify (TYPE_2__*,TYPE_3__) ; 
 int client_handle_compressed_certificate (TYPE_2__*,TYPE_3__) ; 
 int client_handle_encrypted_extensions (TYPE_2__*,TYPE_3__,int /*<<< orphan*/ *) ; 
 int client_handle_finished (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__) ; 
 int client_handle_hello (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ *) ; 
 int client_handle_new_session_ticket (TYPE_2__*,TYPE_3__) ; 
 int handle_key_update (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__) ; 
 int server_handle_certificate (TYPE_2__*,TYPE_3__) ; 
 int server_handle_certificate_verify (TYPE_2__*,TYPE_3__) ; 
 int server_handle_end_of_early_data (TYPE_2__*,TYPE_3__) ; 
 int server_handle_finished (TYPE_2__*,TYPE_3__) ; 
 int server_handle_hello (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_handshake_message(ptls_t *tls, ptls_message_emitter_t *emitter, ptls_iovec_t message, int is_end_of_record,
                                    ptls_handshake_properties_t *properties)
{
    uint8_t type = message.base[0];
    int ret;

    switch (tls->state) {
    case PTLS_STATE_CLIENT_EXPECT_SERVER_HELLO:
    case PTLS_STATE_CLIENT_EXPECT_SECOND_SERVER_HELLO:
        if (type == PTLS_HANDSHAKE_TYPE_SERVER_HELLO && is_end_of_record) {
            ret = client_handle_hello(tls, emitter, message, properties);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_CLIENT_EXPECT_ENCRYPTED_EXTENSIONS:
        if (type == PTLS_HANDSHAKE_TYPE_ENCRYPTED_EXTENSIONS) {
            ret = client_handle_encrypted_extensions(tls, message, properties);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_REQUEST_OR_CERTIFICATE:
        if (type == PTLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST) {
            ret = client_handle_certificate_request(tls, message, properties);
            break;
        }
    /* fall through */
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE:
        switch (type) {
        case PTLS_HANDSHAKE_TYPE_CERTIFICATE:
            ret = client_handle_certificate(tls, message);
            break;
        case PTLS_HANDSHAKE_TYPE_COMPRESSED_CERTIFICATE:
            ret = client_handle_compressed_certificate(tls, message);
            break;
        default:
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
            break;
        }
        break;
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY:
        if (type == PTLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY) {
            ret = client_handle_certificate_verify(tls, message);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_CLIENT_EXPECT_FINISHED:
        if (type == PTLS_HANDSHAKE_TYPE_FINISHED && is_end_of_record) {
            ret = client_handle_finished(tls, emitter, message);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_SERVER_EXPECT_CLIENT_HELLO:
    case PTLS_STATE_SERVER_EXPECT_SECOND_CLIENT_HELLO:
        if (type == PTLS_HANDSHAKE_TYPE_CLIENT_HELLO && is_end_of_record) {
            ret = server_handle_hello(tls, emitter, message, properties);
        } else {
            ret = PTLS_ALERT_HANDSHAKE_FAILURE;
        }
        break;
    case PTLS_STATE_SERVER_EXPECT_CERTIFICATE:
        if (type == PTLS_HANDSHAKE_TYPE_CERTIFICATE) {
            ret = server_handle_certificate(tls, message);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_SERVER_EXPECT_CERTIFICATE_VERIFY:
        if (type == PTLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY) {
            ret = server_handle_certificate_verify(tls, message);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_SERVER_EXPECT_END_OF_EARLY_DATA:
        assert(!tls->ctx->omit_end_of_early_data);
        if (type == PTLS_HANDSHAKE_TYPE_END_OF_EARLY_DATA) {
            ret = server_handle_end_of_early_data(tls, message);
        } else {
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
        }
        break;
    case PTLS_STATE_SERVER_EXPECT_FINISHED:
        if (type == PTLS_HANDSHAKE_TYPE_FINISHED && is_end_of_record) {
            ret = server_handle_finished(tls, message);
        } else {
            ret = PTLS_ALERT_HANDSHAKE_FAILURE;
        }
        break;
    case PTLS_STATE_CLIENT_POST_HANDSHAKE:
        switch (type) {
        case PTLS_HANDSHAKE_TYPE_NEW_SESSION_TICKET:
            ret = client_handle_new_session_ticket(tls, message);
            break;
        case PTLS_HANDSHAKE_TYPE_KEY_UPDATE:
            ret = handle_key_update(tls, emitter, message);
            break;
        default:
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
            break;
        }
        break;
    case PTLS_STATE_SERVER_POST_HANDSHAKE:
        switch (type) {
        case PTLS_HANDSHAKE_TYPE_KEY_UPDATE:
            ret = handle_key_update(tls, emitter, message);
            break;
        default:
            ret = PTLS_ALERT_UNEXPECTED_MESSAGE;
            break;
        }
        break;
    default:
        assert(!"unexpected state");
        break;
    }

    PTLS_PROBE(RECEIVE_MESSAGE, tls, message.base[0], message.base + PTLS_HANDSHAKE_HEADER_SIZE,
               message.len - PTLS_HANDSHAKE_HEADER_SIZE, ret);

    return ret;
}