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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  on_read_alloc ; 
 int /*<<< orphan*/  on_tcp_child_process_read ; 
 int uv_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_child_process_cb(uv_connect_t* req, int status) {
  int r;

  ASSERT(status == 0);
  r = uv_read_start(req->handle, on_read_alloc, on_tcp_child_process_read);
  ASSERT(r == 0);
}