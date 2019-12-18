#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* _header; } ;
typedef  TYPE_2__ ldns_pkt ;
struct TYPE_4__ {int /*<<< orphan*/  _rcode; } ;

/* Variables and functions */

void
ldns_pkt_set_rcode(ldns_pkt *packet, uint8_t rcode)
{
	packet->_header->_rcode = rcode;
}