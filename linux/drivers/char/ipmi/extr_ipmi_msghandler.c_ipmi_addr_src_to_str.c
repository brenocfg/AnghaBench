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
typedef  enum ipmi_addr_src { ____Placeholder_ipmi_addr_src } ipmi_addr_src ;

/* Variables and functions */
 int SI_LAST ; 
 char const** addr_src_to_str ; 

const char *ipmi_addr_src_to_str(enum ipmi_addr_src src)
{
	if (src >= SI_LAST)
		src = 0; /* Invalid */
	return addr_src_to_str[src];
}