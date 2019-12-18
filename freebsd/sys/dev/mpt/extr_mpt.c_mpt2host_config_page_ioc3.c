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
typedef  int /*<<< orphan*/  CONFIG_PAGE_IOC_3 ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_2_HOST16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Reserved2 ; 

void
mpt2host_config_page_ioc3(CONFIG_PAGE_IOC_3 *ioc3)
{

	MPT_2_HOST16(ioc3, Reserved2);
}