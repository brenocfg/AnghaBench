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
struct platform_msi_priv_data {void* host_data; } ;
struct irq_domain {struct platform_msi_priv_data* host_data; } ;

/* Variables and functions */

void *platform_msi_get_host_data(struct irq_domain *domain)
{
	struct platform_msi_priv_data *data = domain->host_data;
	return data->host_data;
}