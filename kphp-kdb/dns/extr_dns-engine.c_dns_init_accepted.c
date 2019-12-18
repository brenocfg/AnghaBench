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
struct connection {int /*<<< orphan*/  last_query_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  dns_tcp_connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  now ; 
 TYPE_1__ wstat ; 

int dns_init_accepted (struct connection *c) {
  wstat.dns_tcp_connections++;
  c->last_query_time = now;
  return 0;
}