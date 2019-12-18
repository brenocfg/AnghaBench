#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  conn_alloc_cb ; 
 int /*<<< orphan*/  conn_read_cb ; 
 int /*<<< orphan*/  connection_cb_called ; 
 int /*<<< orphan*/  incoming ; 
 scalar_t__ uv_accept (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* tcp, int status) {
  ASSERT(status == 0);

  ASSERT(0 == uv_tcp_init(tcp->loop, &incoming));
  ASSERT(0 == uv_accept(tcp, (uv_stream_t*) &incoming));
  ASSERT(0 == uv_read_start((uv_stream_t*) &incoming,
                            conn_alloc_cb,
                            conn_read_cb));

  connection_cb_called++;
}