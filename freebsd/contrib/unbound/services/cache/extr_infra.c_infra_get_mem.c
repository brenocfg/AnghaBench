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
struct infra_cache {scalar_t__ client_ip_rates; scalar_t__ domain_rates; scalar_t__ hosts; } ;

/* Variables and functions */
 size_t slabhash_get_mem (scalar_t__) ; 

size_t 
infra_get_mem(struct infra_cache* infra)
{
	size_t s = sizeof(*infra) + slabhash_get_mem(infra->hosts);
	if(infra->domain_rates) s += slabhash_get_mem(infra->domain_rates);
	if(infra->client_ip_rates) s += slabhash_get_mem(infra->client_ip_rates);
	/* ignore domain_limits because walk through tree is big */
	return s;
}