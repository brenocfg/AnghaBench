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
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3_ingress_unistream_t {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  enc; } ;
struct TYPE_5__ {TYPE_1__ qpack; } ;
typedef  TYPE_2__ h2o_http3_conn_t ;

/* Variables and functions */
 int h2o_qpack_encoder_handle_input (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static int qpack_decoder_stream_handle_input(h2o_http3_conn_t *conn, struct st_h2o_http3_ingress_unistream_t *stream,
                                             const uint8_t **src, const uint8_t *src_end, const char **err_desc)
{
    while (*src != src_end) {
        int ret;
        if ((ret = h2o_qpack_encoder_handle_input(conn->qpack.enc, src, src_end, err_desc)) != 0)
            return ret;
    }
    return 0;
}