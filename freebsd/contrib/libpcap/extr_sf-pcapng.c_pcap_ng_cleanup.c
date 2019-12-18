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
struct pcap_ng_sf {int /*<<< orphan*/  ifaces; } ;
struct TYPE_4__ {struct pcap_ng_sf* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sf_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void
pcap_ng_cleanup(pcap_t *p)
{
	struct pcap_ng_sf *ps = p->priv;

	free(ps->ifaces);
	sf_cleanup(p);
}