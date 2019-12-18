#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  insert_count; } ;
typedef  TYPE_1__ h2o_qpack_decoder_t ;

/* Variables and functions */
 scalar_t__* h2o_hpack_encode_int (scalar_t__*,int /*<<< orphan*/ ,int) ; 

size_t h2o_qpack_decoder_send_state_sync(h2o_qpack_decoder_t *qpack, uint8_t *outbuf)
{
    if (qpack->insert_count == 0)
        return 0;

    uint8_t *dst = outbuf;
    *dst = 0;
    dst = h2o_hpack_encode_int(dst, qpack->insert_count, 6);
    qpack->insert_count = 0;

    return dst - outbuf;
}