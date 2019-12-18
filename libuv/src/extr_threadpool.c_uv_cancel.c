#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct uv__work {int dummy; } ;
struct TYPE_9__ {struct uv__work work_req; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_work_t ;
struct TYPE_10__ {int type; } ;
typedef  TYPE_2__ uv_req_t ;
struct TYPE_11__ {struct uv__work work_req; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_3__ uv_random_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_12__ {struct uv__work work_req; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_4__ uv_getnameinfo_t ;
struct TYPE_13__ {struct uv__work work_req; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_5__ uv_getaddrinfo_t ;
struct TYPE_14__ {struct uv__work work_req; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_6__ uv_fs_t ;

/* Variables and functions */
 int UV_EINVAL ; 
#define  UV_FS 132 
#define  UV_GETADDRINFO 131 
#define  UV_GETNAMEINFO 130 
#define  UV_RANDOM 129 
#define  UV_WORK 128 
 int uv__work_cancel (int /*<<< orphan*/ *,TYPE_2__*,struct uv__work*) ; 

int uv_cancel(uv_req_t* req) {
  struct uv__work* wreq;
  uv_loop_t* loop;

  switch (req->type) {
  case UV_FS:
    loop =  ((uv_fs_t*) req)->loop;
    wreq = &((uv_fs_t*) req)->work_req;
    break;
  case UV_GETADDRINFO:
    loop =  ((uv_getaddrinfo_t*) req)->loop;
    wreq = &((uv_getaddrinfo_t*) req)->work_req;
    break;
  case UV_GETNAMEINFO:
    loop = ((uv_getnameinfo_t*) req)->loop;
    wreq = &((uv_getnameinfo_t*) req)->work_req;
    break;
  case UV_RANDOM:
    loop = ((uv_random_t*) req)->loop;
    wreq = &((uv_random_t*) req)->work_req;
    break;
  case UV_WORK:
    loop =  ((uv_work_t*) req)->loop;
    wreq = &((uv_work_t*) req)->work_req;
    break;
  default:
    return UV_EINVAL;
  }

  return uv__work_cancel(loop, req, wreq);
}