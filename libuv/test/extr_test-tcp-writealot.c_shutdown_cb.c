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
struct TYPE_5__ {scalar_t__ write_queue_size; } ;
typedef  TYPE_1__ uv_tcp_t ;
struct TYPE_6__ {scalar_t__ handle; } ;
typedef  TYPE_2__ uv_shutdown_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ WRITES ; 
 int /*<<< orphan*/  shutdown_cb_called ; 
 TYPE_2__ shutdown_req ; 
 scalar_t__ write_cb_called ; 

__attribute__((used)) static void shutdown_cb(uv_shutdown_t* req, int status) {
  uv_tcp_t* tcp;

  ASSERT(req == &shutdown_req);
  ASSERT(status == 0);

  tcp = (uv_tcp_t*)(req->handle);

  /* The write buffer should be empty by now. */
  ASSERT(tcp->write_queue_size == 0);

  /* Now we wait for the EOF */
  shutdown_cb_called++;

  /* We should have had all the writes called already. */
  ASSERT(write_cb_called == WRITES);
}