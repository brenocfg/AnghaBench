#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  ptr; int /*<<< orphan*/  type; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int /*<<< orphan*/  ETHER_TYPE_LEN ; 
 int /*<<< orphan*/  packet_adj (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tap_recv(packet_t *pkt)
{

	if (pkt->len < ETHER_HDR_LEN)
		return false;

	pkt->dst = pkt->ptr;
	packet_adj(pkt, ETHER_ADDR_LEN);
	pkt->src = pkt->ptr;
	packet_adj(pkt, ETHER_ADDR_LEN);
	pkt->type = pkt->ptr;
	packet_adj(pkt, ETHER_TYPE_LEN);

	return true;
}