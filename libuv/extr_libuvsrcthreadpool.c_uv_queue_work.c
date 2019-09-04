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
struct TYPE_4__ {int /*<<< orphan*/  work_req; int /*<<< orphan*/  after_work_cb; int /*<<< orphan*/ * work_cb; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_work_t ;
typedef  int /*<<< orphan*/ * uv_work_cb ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_after_work_cb ;

/* Variables and functions */
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_WORK ; 
 int /*<<< orphan*/  UV__WORK_CPU ; 
 int /*<<< orphan*/  uv__queue_done ; 
 int /*<<< orphan*/  uv__queue_work ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__work_submit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb) {
  if (work_cb == NULL)
    return UV_EINVAL;

  uv__req_init(loop, req, UV_WORK);
  req->loop = loop;
  req->work_cb = work_cb;
  req->after_work_cb = after_work_cb;
  uv__work_submit(loop,
                  &req->work_req,
                  UV__WORK_CPU,
                  uv__queue_work,
                  uv__queue_done);
  return 0;
}