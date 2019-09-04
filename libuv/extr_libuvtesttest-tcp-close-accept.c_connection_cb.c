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
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_6__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  alloc_cb ; 
 unsigned int got_connections ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/ * tcp_incoming ; 
 int /*<<< orphan*/  tcp_server ; 
 scalar_t__ uv_accept (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* server, int status) {
  unsigned int i;
  uv_tcp_t* incoming;

  ASSERT(server == (uv_stream_t*) &tcp_server);

  /* Ignore tcp_check connection */
  if (got_connections == ARRAY_SIZE(tcp_incoming))
    return;

  /* Accept everyone */
  incoming = &tcp_incoming[got_connections++];
  ASSERT(0 == uv_tcp_init(server->loop, incoming));
  ASSERT(0 == uv_accept(server, (uv_stream_t*) incoming));

  if (got_connections != ARRAY_SIZE(tcp_incoming))
    return;

  /* Once all clients are accepted - start reading */
  for (i = 0; i < ARRAY_SIZE(tcp_incoming); i++) {
    incoming = &tcp_incoming[i];
    ASSERT(0 == uv_read_start((uv_stream_t*) incoming, alloc_cb, read_cb));
  }
}