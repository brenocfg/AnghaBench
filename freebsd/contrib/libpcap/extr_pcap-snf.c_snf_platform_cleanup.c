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
struct pcap_snf {int /*<<< orphan*/  snf_handle; int /*<<< orphan*/  snf_ring; scalar_t__ snf_inj; } ;
struct TYPE_4__ {struct pcap_snf* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 
 int /*<<< orphan*/  snf_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snf_inject_close (scalar_t__) ; 
 int /*<<< orphan*/  snf_ring_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snf_platform_cleanup(pcap_t *p)
{
	struct pcap_snf *ps = p->priv;

#ifdef SNF_HAVE_INJECT_API
	if (ps->snf_inj)
		snf_inject_close(ps->snf_inj);
#endif
	snf_ring_close(ps->snf_ring);
	snf_close(ps->snf_handle);
	pcap_cleanup_live_common(p);
}