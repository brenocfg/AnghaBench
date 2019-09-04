#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state; int /*<<< orphan*/  key_schedule; } ;
typedef  TYPE_1__ ptls_t ;
struct TYPE_7__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_2__ ptls_iovec_t ;

/* Variables and functions */
 int PTLS_ERROR_IN_PROGRESS ; 
 scalar_t__ PTLS_HANDSHAKE_HEADER_SIZE ; 
 int /*<<< orphan*/  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY ; 
 int client_do_handle_certificate (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int client_handle_certificate(ptls_t *tls, ptls_iovec_t message)
{
    int ret;

    if ((ret = client_do_handle_certificate(tls, message.base + PTLS_HANDSHAKE_HEADER_SIZE, message.base + message.len)) != 0)
        return ret;

    ptls__key_schedule_update_hash(tls->key_schedule, message.base, message.len);

    tls->state = PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY;
    return PTLS_ERROR_IN_PROGRESS;
}