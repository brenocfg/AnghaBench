#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* tid; } ;
typedef  TYPE_1__ tftp_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enable_ipv6 ; 
 TYPE_1__* get_connection_f (int,int) ; 
 int open_udp_server_socket (int) ; 
 int /*<<< orphan*/  tftp_init_udp_port (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_tftp_server ; 
 size_t working_mode ; 

int tftp_init_listening_connection (int port, int udp_sfd) {
  tftp_connection_t *c = get_connection_f (port, 1);
  c->tid[working_mode] = port;
  if (udp_sfd < 0) {
    udp_sfd = open_udp_server_socket (port);
    if (udp_sfd < 0) {
      return -1;
    }
  }
  assert (!tftp_init_udp_port (c, udp_sfd, port, &ut_tftp_server, 0, enable_ipv6));
  return 0;
}