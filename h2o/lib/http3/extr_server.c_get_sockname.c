#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ctx; } ;
struct st_h2o_http3_server_conn_t {TYPE_3__ h3; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  h2o_conn_t ;
struct TYPE_4__ {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static socklen_t get_sockname(h2o_conn_t *_conn, struct sockaddr *sa)
{
    struct st_h2o_http3_server_conn_t *conn = (void *)_conn;
    memcpy(sa, &conn->h3.ctx->sock.addr, conn->h3.ctx->sock.addrlen);
    return conn->h3.ctx->sock.addrlen;
}