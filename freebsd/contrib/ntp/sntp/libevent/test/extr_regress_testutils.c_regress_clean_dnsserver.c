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
 scalar_t__ dns_port ; 
 scalar_t__ dns_sock ; 
 int /*<<< orphan*/  evdns_close_server_port (scalar_t__) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 

void
regress_clean_dnsserver(void)
{
	if (dns_port)
		evdns_close_server_port(dns_port);
	if (dns_sock >= 0)
		evutil_closesocket(dns_sock);
}