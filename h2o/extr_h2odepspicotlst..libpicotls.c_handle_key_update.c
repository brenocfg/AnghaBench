#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int needs_key_update; TYPE_1__* ctx; } ;
typedef  TYPE_2__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_9__ {int* base; int len; } ;
typedef  TYPE_3__ ptls_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/ * update_traffic_key; } ;

/* Variables and functions */
 int PTLS_ALERT_DECODE_ERROR ; 
 int PTLS_ALERT_UNEXPECTED_MESSAGE ; 
 int PTLS_HANDSHAKE_HEADER_SIZE ; 
 int update_traffic_key (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_key_update(ptls_t *tls, ptls_message_emitter_t *emitter, ptls_iovec_t message)
{
    const uint8_t *src = message.base + PTLS_HANDSHAKE_HEADER_SIZE, *const end = message.base + message.len;
    int ret;

    /* validate */
    if (end - src != 1 || *src > 1)
        return PTLS_ALERT_DECODE_ERROR;

    /* update receive key */
    if ((ret = update_traffic_key(tls, 0)) != 0)
        return ret;

    if (*src) {
        if (tls->ctx->update_traffic_key != NULL)
            return PTLS_ALERT_UNEXPECTED_MESSAGE;
        tls->needs_key_update = 1;
    }

    return 0;
}