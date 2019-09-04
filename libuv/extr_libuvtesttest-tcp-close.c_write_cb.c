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
struct TYPE_4__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ close_cb_called ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tcp_handle ; 
 int /*<<< orphan*/  write_cb_called ; 

__attribute__((used)) static void write_cb(uv_write_t* req, int status) {
  /* write callbacks should run before the close callback */
  ASSERT(close_cb_called == 0);
  ASSERT(req->handle == (uv_stream_t*)&tcp_handle);
  write_cb_called++;
  free(req);
}