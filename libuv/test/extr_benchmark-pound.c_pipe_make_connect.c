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
typedef  int /*<<< orphan*/  uv_pipe_t ;
struct TYPE_10__ {int /*<<< orphan*/  conn_req; } ;
typedef  TYPE_4__ pipe_conn_rec ;
struct TYPE_9__ {TYPE_5__* data; } ;
struct TYPE_8__ {TYPE_5__* data; } ;
struct TYPE_7__ {TYPE_5__* data; } ;
struct TYPE_11__ {int i; TYPE_3__ stream; TYPE_2__ write_req; TYPE_1__ conn_req; } ;
typedef  TYPE_5__ conn_rec ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PIPENAME ; 
 int /*<<< orphan*/  connect_cb ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  uv_pipe_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_make_connect(conn_rec* p) {
  int r;

  r = uv_pipe_init(loop, (uv_pipe_t*)&p->stream, 0);
  ASSERT(r == 0);

  uv_pipe_connect(&((pipe_conn_rec*) p)->conn_req,
                  (uv_pipe_t*) &p->stream,
                  TEST_PIPENAME,
                  connect_cb);

#if DEBUG
  printf("make connect %d\n", p->i);
#endif

  p->conn_req.data = p;
  p->write_req.data = p;
  p->stream.data = p;
}