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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  UDP ; 
 int /*<<< orphan*/  echo_alloc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  on_recv ; 
 int /*<<< orphan*/ * server ; 
 int /*<<< orphan*/  serverType ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  udpServer ; 
 char* uv_strerror (int) ; 
 int uv_udp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_udp_recv_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp4_echo_start(int port) {
  int r;

  server = (uv_handle_t*)&udpServer;
  serverType = UDP;

  r = uv_udp_init(loop, &udpServer);
  if (r) {
    fprintf(stderr, "uv_udp_init: %s\n", uv_strerror(r));
    return 1;
  }

  r = uv_udp_recv_start(&udpServer, echo_alloc, on_recv);
  if (r) {
    fprintf(stderr, "uv_udp_recv_start: %s\n", uv_strerror(r));
    return 1;
  }

  return 0;
}