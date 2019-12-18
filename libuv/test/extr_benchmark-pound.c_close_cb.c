#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_handle_t ;
struct TYPE_6__ {int i; int /*<<< orphan*/  (* make_connect ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ conn_rec ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closed_streams ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int start ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int uv_now (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_cb(uv_handle_t* handle) {
  conn_rec* p = (conn_rec*)handle->data;

  ASSERT(handle != NULL);
  closed_streams++;

#if DEBUG
  printf("close_cb %d\n", p->i);
#endif

  if (uv_now(loop) - start < 10000) {
    p->make_connect(p);
  }
}