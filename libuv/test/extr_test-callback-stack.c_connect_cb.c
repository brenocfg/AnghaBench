#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_5__ {scalar_t__ handle; } ;
typedef  TYPE_1__ uv_connect_t ;
struct TYPE_6__ {char* base; int len; } ;
typedef  TYPE_2__ uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  MESSAGE ; 
 int /*<<< orphan*/  connect_cb_called ; 
 scalar_t__ nested ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  uv_buf_t buf;

  puts("Connected. Write some data to echo server...");

  ASSERT(status == 0);
  ASSERT(nested == 0 && "connect_cb must be called from a fresh stack");

  nested++;

  buf.base = (char*) &MESSAGE;
  buf.len = sizeof MESSAGE;

  if (uv_write(&write_req, (uv_stream_t*)req->handle, &buf, 1, write_cb)) {
    FATAL("uv_write failed");
  }

  nested--;

  connect_cb_called++;
}