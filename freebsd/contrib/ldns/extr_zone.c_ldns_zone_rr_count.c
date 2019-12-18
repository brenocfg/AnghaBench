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
struct TYPE_3__ {int /*<<< orphan*/  _rrs; } ;
typedef  TYPE_1__ ldns_zone ;

/* Variables and functions */
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ ) ; 

size_t
ldns_zone_rr_count(const ldns_zone *z)
{
	return ldns_rr_list_rr_count(z->_rrs);
}