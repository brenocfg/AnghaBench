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
 int domain_is_valid (unsigned int) ; 
 int interface_version ; 
 int is_physical_domain (unsigned int) ; 

__attribute__((used)) static bool catalog_entry_domain_is_valid(unsigned domain)
{
	/* POWER8 doesn't support virtual domains. */
	if (interface_version == 1)
		return is_physical_domain(domain);
	else
		return domain_is_valid(domain);
}