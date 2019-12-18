#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int write_index; int nbufs; TYPE_1__* handle; int /*<<< orphan*/ * bufs; } ;
typedef  TYPE_2__ uv_write_t ;
struct TYPE_4__ {size_t write_queue_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t uv__count_bufs (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t uv__write_req_size(uv_write_t* req) {
  size_t size;

  assert(req->bufs != NULL);
  size = uv__count_bufs(req->bufs + req->write_index,
                        req->nbufs - req->write_index);
  assert(req->handle->write_queue_size >= size);

  return size;
}