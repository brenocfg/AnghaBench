#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int REQ_COUNT ; 
 int /*<<< orphan*/  connect_cb_called ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 
 int /*<<< orphan*/ * write_requests ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  static char base[1024];
  int r;
  int i;
  uv_buf_t buf;

  ASSERT(status == 0);
  connect_cb_called++;

  buf = uv_buf_init(base, sizeof(base));

  for (i = 0; i < REQ_COUNT; i++) {
    r = uv_write(&write_requests[i],
                 req->handle,
                 &buf,
                 1,
                 write_cb);
    ASSERT(r == 0);
  }
}