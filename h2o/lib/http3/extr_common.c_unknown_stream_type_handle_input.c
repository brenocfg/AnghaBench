#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3_ingress_unistream_t {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_http3_conn_t ;

/* Variables and functions */

__attribute__((used)) static int unknown_stream_type_handle_input(h2o_http3_conn_t *conn, struct st_h2o_http3_ingress_unistream_t *stream,
                                            const uint8_t **src, const uint8_t *src_end, const char **err_desc)
{
    /* just consume the input */
    *src = src_end;
    return 0;
}