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
struct TYPE_4__ {size_t buflen; int /*<<< orphan*/  work_req; void* buf; int /*<<< orphan*/ * cb; scalar_t__ status; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_random_t ;
typedef  int /*<<< orphan*/ * uv_random_cb ;
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int UV_E2BIG ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_RANDOM ; 
 int /*<<< orphan*/  UV__WORK_CPU ; 
 int uv__random (void*,size_t) ; 
 int /*<<< orphan*/  uv__random_done ; 
 int /*<<< orphan*/  uv__random_work ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__work_submit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv_random(uv_loop_t* loop,
              uv_random_t* req,
              void *buf,
              size_t buflen,
              unsigned flags,
              uv_random_cb cb) {
  if (buflen > 0x7FFFFFFFu)
    return UV_E2BIG;

  if (flags != 0)
    return UV_EINVAL;

  if (cb == NULL)
    return uv__random(buf, buflen);

  uv__req_init(loop, req, UV_RANDOM);
  req->loop = loop;
  req->status = 0;
  req->cb = cb;
  req->buf = buf;
  req->buflen = buflen;

  uv__work_submit(loop,
                  &req->work_req,
                  UV__WORK_CPU,
                  uv__random_work,
                  uv__random_done);

  return 0;
}