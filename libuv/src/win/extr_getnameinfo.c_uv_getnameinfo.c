#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_5__ {int flags; int retcode; int /*<<< orphan*/  work_req; int /*<<< orphan*/ * loop; scalar_t__ getnameinfo_cb; int /*<<< orphan*/  storage; } ;
typedef  TYPE_1__ uv_getnameinfo_t ;
typedef  scalar_t__ uv_getnameinfo_cb ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_GETNAMEINFO ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV__WORK_SLOW_IO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  uv__getnameinfo_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__getnameinfo_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__req_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uv__work_submit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 

int uv_getnameinfo(uv_loop_t* loop,
                   uv_getnameinfo_t* req,
                   uv_getnameinfo_cb getnameinfo_cb,
                   const struct sockaddr* addr,
                   int flags) {
  if (req == NULL || addr == NULL)
    return UV_EINVAL;

  if (addr->sa_family == AF_INET) {
    memcpy(&req->storage,
           addr,
           sizeof(struct sockaddr_in));
  } else if (addr->sa_family == AF_INET6) {
    memcpy(&req->storage,
           addr,
           sizeof(struct sockaddr_in6));
  } else {
    return UV_EINVAL;
  }

  UV_REQ_INIT(req, UV_GETNAMEINFO);
  uv__req_register(loop, req);

  req->getnameinfo_cb = getnameinfo_cb;
  req->flags = flags;
  req->loop = loop;
  req->retcode = 0;

  if (getnameinfo_cb) {
    uv__work_submit(loop,
                    &req->work_req,
                    UV__WORK_SLOW_IO,
                    uv__getnameinfo_work,
                    uv__getnameinfo_done);
    return 0;
  } else {
    uv__getnameinfo_work(&req->work_req);
    uv__getnameinfo_done(&req->work_req, 0);
    return req->retcode;
  }
}