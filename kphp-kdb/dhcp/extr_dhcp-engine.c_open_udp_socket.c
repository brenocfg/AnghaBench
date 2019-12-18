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
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 scalar_t__ SM_UDP ; 
 int /*<<< orphan*/  backlog ; 
 char* conv_addr (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ enable_ipv6 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int server_socket (int,struct in_addr,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ verbosity ; 

int open_udp_socket (int port) {
  static struct in_addr settings_addr;
  char buf2[256];
  int sfd = server_socket (port, settings_addr, backlog, SM_UDP + enable_ipv6);
  if (sfd < 0) {
    kprintf ("cannot open UDP server socket at port %d: %m\n", port);
    exit (1);
  }
  if (verbosity) {
    printf ("created listening udp socket at %s:%d, fd=%d\n", conv_addr (settings_addr.s_addr, buf2), port, sfd);
  }
  return sfd;
}