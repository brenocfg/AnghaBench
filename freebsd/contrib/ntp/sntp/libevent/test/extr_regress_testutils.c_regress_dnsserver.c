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
struct regress_dns_server_table {int dummy; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dns_port ; 
 int /*<<< orphan*/  dns_sock ; 
 int /*<<< orphan*/  regress_dns_server_cb ; 
 int /*<<< orphan*/ * regress_get_dnsserver (struct event_base*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regress_dns_server_table*) ; 

int
regress_dnsserver(struct event_base *base, ev_uint16_t *port,
    struct regress_dns_server_table *search_table)
{
	dns_port = regress_get_dnsserver(base, port, &dns_sock,
	    regress_dns_server_cb, search_table);
	return dns_port != NULL;
}