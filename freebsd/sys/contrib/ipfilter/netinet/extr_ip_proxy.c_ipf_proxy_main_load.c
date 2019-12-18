#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* apr_load ) () ;scalar_t__ apr_p; } ;
typedef  TYPE_1__ aproxy_t ;

/* Variables and functions */
 TYPE_1__* ips_proxies ; 
 int /*<<< orphan*/  stub1 () ; 

int
ipf_proxy_main_load()
{
	aproxy_t *ap;

	for (ap = ips_proxies; ap->apr_p; ap++) {
		if (ap->apr_load != NULL)
			(*ap->apr_load)();
	}
	return 0;
}