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
struct ms_hyperv_tsc_page {int dummy; } ;

/* Variables and functions */
 struct ms_hyperv_tsc_page tsc_pg ; 

struct ms_hyperv_tsc_page *hv_get_tsc_page(void)
{
	return &tsc_pg;
}