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
struct TYPE_4__ {int /*<<< orphan*/  (* apr_unload ) () ;struct TYPE_4__* apr_next; scalar_t__ apr_p; } ;
typedef  TYPE_1__ aproxy_t ;

/* Variables and functions */
 TYPE_1__* ap_proxylist ; 
 TYPE_1__* ips_proxies ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int
ipf_proxy_main_unload()
{
	aproxy_t *ap;

	for (ap = ips_proxies; ap->apr_p; ap++)
		if (ap->apr_unload != NULL)
			(*ap->apr_unload)();
	for (ap = ap_proxylist; ap; ap = ap->apr_next)
		if (ap->apr_unload != NULL)
			(*ap->apr_unload)();

	return 0;
}