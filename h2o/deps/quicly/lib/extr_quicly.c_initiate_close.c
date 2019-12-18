#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {char const* reason_phrase; int /*<<< orphan*/  frame_type; scalar_t__ error_code; } ;
struct TYPE_8__ {TYPE_1__ connection_close; } ;
struct TYPE_9__ {scalar_t__ state; } ;
struct TYPE_10__ {TYPE_2__ egress; TYPE_3__ super; } ;
typedef  TYPE_4__ quicly_conn_t ;

/* Variables and functions */
 scalar_t__ PTLS_ERROR_CLASS_SELF_ALERT ; 
 scalar_t__ PTLS_ERROR_GET_CLASS (int) ; 
 scalar_t__ PTLS_ERROR_TO_ALERT (int) ; 
 scalar_t__ QUICLY_ERROR_GET_ERROR_CODE (int) ; 
 scalar_t__ QUICLY_ERROR_IS_QUIC_APPLICATION (int) ; 
 scalar_t__ QUICLY_ERROR_IS_QUIC_TRANSPORT (int) ; 
 scalar_t__ QUICLY_STATE_CLOSING ; 
 int QUICLY_TRANSPORT_ERROR_INTERNAL ; 
 scalar_t__ QUICLY_TRANSPORT_ERROR_TLS_ALERT_BASE ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int enter_close (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int initiate_close(quicly_conn_t *conn, int err, uint64_t frame_type, const char *reason_phrase)
{
    uint16_t quic_error_code;

    if (conn->super.state >= QUICLY_STATE_CLOSING)
        return 0;

    if (reason_phrase == NULL)
        reason_phrase = "";

    /* convert error code to QUIC error codes */
    if (QUICLY_ERROR_IS_QUIC_TRANSPORT(err)) {
        quic_error_code = QUICLY_ERROR_GET_ERROR_CODE(err);
    } else if (QUICLY_ERROR_IS_QUIC_APPLICATION(err)) {
        quic_error_code = QUICLY_ERROR_GET_ERROR_CODE(err);
        frame_type = UINT64_MAX;
    } else if (PTLS_ERROR_GET_CLASS(err) == PTLS_ERROR_CLASS_SELF_ALERT) {
        quic_error_code = QUICLY_TRANSPORT_ERROR_TLS_ALERT_BASE + PTLS_ERROR_TO_ALERT(err);
    } else {
        quic_error_code = QUICLY_ERROR_GET_ERROR_CODE(QUICLY_TRANSPORT_ERROR_INTERNAL);
        frame_type = UINT64_MAX;
    }

    conn->egress.connection_close.error_code = quic_error_code;
    conn->egress.connection_close.frame_type = frame_type;
    conn->egress.connection_close.reason_phrase = reason_phrase;
    return enter_close(conn, 1, 0);
}