#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http2client_stream_t {TYPE_2__* conn; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sock; } ;
struct TYPE_4__ {TYPE_1__ super; } ;

/* Variables and functions */

__attribute__((used)) static h2o_socket_t *do_get_socket(h2o_httpclient_t *_client)
{
    struct st_h2o_http2client_stream_t *stream = (void *)_client;
    return stream->conn->super.sock;
}