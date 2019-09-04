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
struct st_h2o_http1_conn_t {int /*<<< orphan*/  req; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION ; 
 int /*<<< orphan*/  h2o_send_error_400 (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_bad_request(struct st_h2o_http1_conn_t *conn, const char *body)
{
    h2o_socket_read_stop(conn->sock);
    h2o_send_error_400(&conn->req, "Bad Request", body, H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION);
}