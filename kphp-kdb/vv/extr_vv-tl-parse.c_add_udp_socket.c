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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/  default_udp_socket ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_udp_port (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  settings_addr ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_udp_server ; 
 int /*<<< orphan*/  tl_udp_server_methods ; 
 scalar_t__ usfd ; 

void add_udp_socket (int port, int mode) {
  if (!usfd) {
    usfd = server_socket (port, settings_addr, backlog, mode + 1);
    if (usfd < 0) {
      fprintf (stderr, "cannot open udp port: %m\n");
      exit (1);
    }
  }
  assert ((default_udp_socket = init_udp_port (usfd, port, &tl_udp_server, &tl_udp_server_methods, 1 + mode)));
}