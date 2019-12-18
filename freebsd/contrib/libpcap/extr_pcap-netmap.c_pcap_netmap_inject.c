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
struct pcap_netmap {struct nm_desc* d; } ;
struct nm_desc {int dummy; } ;
struct TYPE_3__ {struct pcap_netmap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int nm_inject (struct nm_desc*,void const*,size_t) ; 

__attribute__((used)) static int
pcap_netmap_inject(pcap_t *p, const void *buf, size_t size)
{
	struct pcap_netmap *pn = p->priv;
	struct nm_desc *d = pn->d;

	return nm_inject(d, buf, size);
}