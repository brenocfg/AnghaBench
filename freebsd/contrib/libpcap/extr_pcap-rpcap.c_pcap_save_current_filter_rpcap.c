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
struct pcap_rpcap {int rmt_flags; scalar_t__ currentfilter; scalar_t__ rmt_clientside; } ;
struct TYPE_3__ {struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int PCAP_OPENFLAG_NOCAPTURE_RPCAP ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static void
pcap_save_current_filter_rpcap(pcap_t *fp, const char *filter)
{
	struct pcap_rpcap *pr = fp->priv;	/* structure used when doing a remote live capture */

	/*
	 * Check if:
	 *  - We are on an remote capture
	 *  - we do not want to capture RPCAP traffic
	 *
	 * If so, we have to save the current filter, because we have to
	 * add some piece of stuff later
	 */
	if (pr->rmt_clientside &&
	    (pr->rmt_flags & PCAP_OPENFLAG_NOCAPTURE_RPCAP))
	{
		if (pr->currentfilter)
			free(pr->currentfilter);

		if (filter == NULL)
			filter = "";

		pr->currentfilter = strdup(filter);
	}
}