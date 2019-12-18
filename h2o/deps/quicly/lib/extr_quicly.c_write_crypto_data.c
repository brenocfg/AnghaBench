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
typedef  int /*<<< orphan*/  quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_3__ {scalar_t__ off; scalar_t__ base; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int quicly_streambuf_egress_write (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

__attribute__((used)) static int write_crypto_data(quicly_conn_t *conn, ptls_buffer_t *tlsbuf, size_t epoch_offsets[5])
{
    size_t epoch;
    int ret;

    if (tlsbuf->off == 0)
        return 0;

    for (epoch = 0; epoch < 4; ++epoch) {
        size_t len = epoch_offsets[epoch + 1] - epoch_offsets[epoch];
        if (len == 0)
            continue;
        quicly_stream_t *stream = quicly_get_stream(conn, -(quicly_stream_id_t)(1 + epoch));
        assert(stream != NULL);
        if ((ret = quicly_streambuf_egress_write(stream, tlsbuf->base + epoch_offsets[epoch], len)) != 0)
            return ret;
    }

    return 0;
}