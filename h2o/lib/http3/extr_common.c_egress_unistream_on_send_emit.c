#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http3_egress_unistream_t {TYPE_1__* sendbuf; } ;
struct TYPE_5__ {struct st_h2o_http3_egress_unistream_t* data; } ;
typedef  TYPE_2__ quicly_stream_t ;
struct TYPE_4__ {size_t size; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 

__attribute__((used)) static int egress_unistream_on_send_emit(quicly_stream_t *qs, size_t off, void *dst, size_t *len, int *wrote_all)
{
    struct st_h2o_http3_egress_unistream_t *stream = qs->data;

    if (*len >= stream->sendbuf->size - off) {
        *len = stream->sendbuf->size - off;
        *wrote_all = 1;
    } else {
        *wrote_all = 0;
    }
    memcpy(dst, stream->sendbuf->bytes + off, *len);
    return 0;
}