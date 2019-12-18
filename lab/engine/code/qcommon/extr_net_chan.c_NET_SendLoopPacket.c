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
typedef  int netsrc_t ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_5__ {int send; TYPE_1__* msgs; } ;
typedef  TYPE_2__ loopback_t ;
struct TYPE_4__ {int datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int MAX_LOOPBACK ; 
 TYPE_2__* loopbacks ; 

void NET_SendLoopPacket (netsrc_t sock, int length, const void *data, netadr_t to)
{
	int		i;
	loopback_t	*loop;

	loop = &loopbacks[sock^1];

	i = loop->send & (MAX_LOOPBACK-1);
	loop->send++;

	Com_Memcpy (loop->msgs[i].data, data, length);
	loop->msgs[i].datalen = length;
}