#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verify_data ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  secret; } ;
struct TYPE_11__ {TYPE_1__ dec; } ;
struct TYPE_14__ {TYPE_9__* key_schedule; TYPE_2__ traffic_protection; } ;
typedef  TYPE_5__ ptls_t ;
struct TYPE_15__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_6__ ptls_iovec_t ;
struct TYPE_16__ {TYPE_4__* hashes; } ;
struct TYPE_13__ {TYPE_3__* algo; } ;
struct TYPE_12__ {scalar_t__ digest_size; } ;

/* Variables and functions */
 int PTLS_ALERT_DECODE_ERROR ; 
 int PTLS_ALERT_HANDSHAKE_FAILURE ; 
 scalar_t__ PTLS_HANDSHAKE_HEADER_SIZE ; 
 int PTLS_MAX_DIGEST_SIZE ; 
 int calc_verify_data (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_mem_equal (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int verify_finished(ptls_t *tls, ptls_iovec_t message)
{
    uint8_t verify_data[PTLS_MAX_DIGEST_SIZE];
    int ret;

    if (PTLS_HANDSHAKE_HEADER_SIZE + tls->key_schedule->hashes[0].algo->digest_size != message.len) {
        ret = PTLS_ALERT_DECODE_ERROR;
        goto Exit;
    }

    if ((ret = calc_verify_data(verify_data, tls->key_schedule, tls->traffic_protection.dec.secret)) != 0)
        goto Exit;
    if (!ptls_mem_equal(message.base + PTLS_HANDSHAKE_HEADER_SIZE, verify_data, tls->key_schedule->hashes[0].algo->digest_size)) {
        ret = PTLS_ALERT_HANDSHAKE_FAILURE;
        goto Exit;
    }

Exit:
    ptls_clear_memory(verify_data, sizeof(verify_data));
    return ret;
}