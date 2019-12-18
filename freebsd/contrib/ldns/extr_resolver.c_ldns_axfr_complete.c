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
struct TYPE_3__ {int _axfr_soa_count; } ;
typedef  TYPE_1__ ldns_resolver ;

/* Variables and functions */

bool
ldns_axfr_complete(const ldns_resolver *res)
{
	/* complete when soa count is 2? */
	return res->_axfr_soa_count == 2;
}