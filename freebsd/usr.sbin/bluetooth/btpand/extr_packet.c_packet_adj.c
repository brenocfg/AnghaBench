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
struct TYPE_3__ {scalar_t__ refcnt; size_t len; size_t ptr; } ;
typedef  TYPE_1__ packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
packet_adj(packet_t *pkt, size_t size)
{

	assert(pkt->refcnt == 0);
	assert(pkt->len >= size);

	pkt->ptr += size;
	pkt->len -= size;
}