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
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ uv_write_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int shutdown_cb_called ; 
 scalar_t__ shutdown_requested ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void (*) (TYPE_1__*,int)) ; 
 int /*<<< orphan*/  write_cb_called ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void write1_cb(uv_write_t* req, int status) {
  uv_buf_t buf;
  int r;

  ASSERT(req != NULL);
  if (status) {
    ASSERT(shutdown_cb_called);
    return;
  }

  if (shutdown_requested)
    return;

  buf = uv_buf_init("P", 1);
  r = uv_write(&write_req, req->handle, &buf, 1, write1_cb);
  ASSERT(r == 0);

  write_cb_called++;
}