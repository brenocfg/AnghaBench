#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_13__ {TYPE_1__ context; } ;
struct TYPE_10__ {TYPE_6__ certificate_request; } ;
struct TYPE_11__ {int /*<<< orphan*/  key_schedule; int /*<<< orphan*/  state; TYPE_2__ client; } ;
typedef  TYPE_3__ ptls_t ;
struct TYPE_12__ {int len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_4__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;

/* Variables and functions */
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 int PTLS_ERROR_IN_PROGRESS ; 
 int PTLS_HANDSHAKE_HEADER_SIZE ; 
 int /*<<< orphan*/  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE ; 
 int decode_certificate_request (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int client_handle_certificate_request(ptls_t *tls, ptls_iovec_t message, ptls_handshake_properties_t *properties)
{
    const uint8_t *src = message.base + PTLS_HANDSHAKE_HEADER_SIZE, *const end = message.base + message.len;
    int ret = 0;

    if ((ret = decode_certificate_request(tls, &tls->client.certificate_request, src, end)) != 0)
        return ret;

    /* This field SHALL be zero length unless used for the post-handshake authentication exchanges (section 4.3.2) */
    if (tls->client.certificate_request.context.len != 0)
        return PTLS_ALERT_ILLEGAL_PARAMETER;

    tls->state = PTLS_STATE_CLIENT_EXPECT_CERTIFICATE;
    ptls__key_schedule_update_hash(tls->key_schedule, message.base, message.len);

    return PTLS_ERROR_IN_PROGRESS;
}