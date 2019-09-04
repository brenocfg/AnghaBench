#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;
struct st_h2o_memcached_resumption_accept_data_t {TYPE_1__ super; int /*<<< orphan*/ * get_req; } ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_socket_ssl_resume_server_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void memcached_resumption_on_get(h2o_iovec_t session_data, void *_accept_data)
{
    struct st_h2o_memcached_resumption_accept_data_t *accept_data = _accept_data;
    accept_data->get_req = NULL;
    h2o_socket_ssl_resume_server_handshake(accept_data->super.sock, session_data);
}