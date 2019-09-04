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
struct in_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ SM_UDP ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ enable_ipv6 ; 
 int server_socket (int,struct in_addr,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int open_udp_server_socket (int port) {
  static struct in_addr settings_addr;
  return server_socket (port, settings_addr, backlog, SM_UDP + enable_ipv6);
}