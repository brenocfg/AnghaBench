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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_begin (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_buffer_limit (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_wire2pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ldns_status
ldns_buffer2pkt_wire(ldns_pkt **packet, const ldns_buffer *buffer)
{
	/* lazy */
	return ldns_wire2pkt(packet, ldns_buffer_begin(buffer),
				ldns_buffer_limit(buffer));

}