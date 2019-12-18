#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 scalar_t__ client_close ; 
 int /*<<< orphan*/  connect_req ; 
 int /*<<< orphan*/  do_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_cb2 ; 
 int /*<<< orphan*/  tcp_client ; 
 int /*<<< orphan*/  uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* conn_req, int status) {
  ASSERT(conn_req == &connect_req);
  uv_read_start((uv_stream_t*) &tcp_client, alloc_cb, read_cb2);
  do_write(&tcp_client);
  if (client_close)
    do_close(&tcp_client);
}