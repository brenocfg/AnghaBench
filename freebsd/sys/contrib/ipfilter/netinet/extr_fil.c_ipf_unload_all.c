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
 int ipf_auth_main_unload () ; 
 int ipf_frag_main_unload () ; 
 int ipf_main_unload () ; 
 int ipf_nat_main_unload () ; 
 int ipf_proxy_main_unload () ; 
 int ipf_state_main_unload () ; 

int
ipf_unload_all()
{
	if (ipf_proxy_main_unload() == -1)
		return -1;

	if (ipf_auth_main_unload() == -1)
		return -1;

	if (ipf_frag_main_unload() == -1)
		return -1;

	if (ipf_nat_main_unload() == -1)
		return -1;

	if (ipf_state_main_unload() == -1)
		return -1;

	if (ipf_main_unload() == -1)
		return -1;

	return 0;
}