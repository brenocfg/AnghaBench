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
 scalar_t__ data_prot ; 
 scalar_t__ request_data_prot ; 
 scalar_t__ sec_complete ; 
 int /*<<< orphan*/  sec_prot_internal (scalar_t__) ; 

void
sec_set_protection_level(void)
{
    if(sec_complete && data_prot != request_data_prot)
	sec_prot_internal(request_data_prot);
}