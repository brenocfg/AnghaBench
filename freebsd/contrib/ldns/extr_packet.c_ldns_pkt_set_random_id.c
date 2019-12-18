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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_get_random () ; 
 int /*<<< orphan*/  ldns_pkt_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ldns_pkt_set_random_id(ldns_pkt *packet)
{
	uint16_t rid = ldns_get_random();
	ldns_pkt_set_id(packet, rid);
}