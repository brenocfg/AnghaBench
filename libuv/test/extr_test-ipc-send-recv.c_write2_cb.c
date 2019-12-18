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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  listen; int /*<<< orphan*/  channel; TYPE_2__ recv2; TYPE_1__ recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__ ctx2 ; 
 scalar_t__ is_child_process ; 
 scalar_t__ is_in_process ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write2_cb_called ; 

__attribute__((used)) static void write2_cb(uv_write_t* req, int status) {
  ASSERT(status == 0);

  /* After two successful writes in the child process, allow the child
   * process to be closed. */
  if (++write2_cb_called == 2 && (is_child_process || is_in_process)) {
    uv_close(&ctx2.recv.handle, NULL);
    uv_close(&ctx2.recv2.handle, NULL);
    uv_close((uv_handle_t*)&ctx2.channel, NULL);
    uv_close((uv_handle_t*)&ctx2.listen, NULL);
  }
}