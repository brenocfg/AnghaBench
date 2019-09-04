#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  connect_cb_called ; 
 TYPE_1__ connect_req ; 
 int /*<<< orphan*/  read1_cb ; 
 int /*<<< orphan*/  timer_cb ; 
 int /*<<< orphan*/  tm ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write1_cb ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void connect1_cb(uv_connect_t* req, int status) {
  uv_buf_t buf;
  uv_stream_t* stream;
  int r;

  ASSERT(req == &connect_req);
  ASSERT(status == 0);

  stream = req->handle;
  connect_cb_called++;

  r = uv_timer_init(uv_default_loop(), &tm);
  ASSERT(r == 0);

  r = uv_timer_start(&tm, timer_cb, 2000, 0);
  ASSERT(r == 0);

  buf = uv_buf_init("P", 1);
  r = uv_write(&write_req, stream, &buf, 1, write1_cb);
  ASSERT(r == 0);

  /* Start reading */
  r = uv_read_start(stream, alloc_cb, read1_cb);
  ASSERT(r == 0);
}