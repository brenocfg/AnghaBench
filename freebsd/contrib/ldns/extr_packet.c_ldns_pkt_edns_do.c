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
struct TYPE_3__ {int _edns_z; } ;
typedef  TYPE_1__ ldns_pkt ;

/* Variables and functions */
 int LDNS_EDNS_MASK_DO_BIT ; 

bool
ldns_pkt_edns_do(const ldns_pkt *packet)
{
	return (packet->_edns_z & LDNS_EDNS_MASK_DO_BIT);
}