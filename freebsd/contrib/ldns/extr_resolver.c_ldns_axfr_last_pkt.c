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
struct TYPE_3__ {int /*<<< orphan*/ * _cur_axfr_pkt; } ;
typedef  TYPE_1__ ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */

ldns_pkt *
ldns_axfr_last_pkt(const ldns_resolver *res)
{
	return res->_cur_axfr_pkt;
}