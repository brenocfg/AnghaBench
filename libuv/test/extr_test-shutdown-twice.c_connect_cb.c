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
 int /*<<< orphan*/  req1 ; 
 int /*<<< orphan*/  req2 ; 
 int /*<<< orphan*/  shutdown_cb ; 
 int uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  int r;

  ASSERT(status == 0);

  r = uv_shutdown(&req1, req->handle, shutdown_cb);
  ASSERT(r == 0);
  r = uv_shutdown(&req2, req->handle, shutdown_cb);
  ASSERT(r != 0);

}