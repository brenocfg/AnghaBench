#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_10__ {int /*<<< orphan*/  conn_req; } ;
typedef  TYPE_4__ tcp_conn_rec ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_9__ {TYPE_5__* data; } ;
struct TYPE_8__ {TYPE_5__* data; } ;
struct TYPE_7__ {TYPE_5__* data; } ;
struct TYPE_11__ {int i; TYPE_3__ stream; TYPE_2__ write_req; TYPE_1__ conn_req; } ;
typedef  TYPE_5__ conn_rec ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  connect_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_err_name (int) ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_make_connect(conn_rec* p) {
  struct sockaddr_in addr;
  tcp_conn_rec* tp;
  int r;

  tp = (tcp_conn_rec*) p;

  r = uv_tcp_init(loop, (uv_tcp_t*)&p->stream);
  ASSERT(r == 0);

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));

  r = uv_tcp_connect(&tp->conn_req,
                     (uv_tcp_t*) &p->stream,
                     (const struct sockaddr*) &addr,
                     connect_cb);
  if (r) {
    fprintf(stderr, "uv_tcp_connect error %s\n", uv_err_name(r));
    ASSERT(0);
  }

#if DEBUG
  printf("make connect %d\n", p->i);
#endif

  p->conn_req.data = p;
  p->write_req.data = p;
  p->stream.data = p;
}