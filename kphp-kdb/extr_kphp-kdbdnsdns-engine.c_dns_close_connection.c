#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dns_tcp_connections; } ;

/* Variables and functions */
 int server_close_connection (struct connection*,int) ; 
 TYPE_1__ wstat ; 

int dns_close_connection (struct connection *c, int who) {
  wstat.dns_tcp_connections--;
  return server_close_connection (c, who);
}