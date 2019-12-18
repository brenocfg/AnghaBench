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
struct TYPE_3__ {int /*<<< orphan*/  errbuf; scalar_t__ activated; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int PCAP_ERROR ; 
 int PCAP_ERROR_NOT_ACTIVATED ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
pcap_not_initialized(pcap_t *pcap)
{
	if (pcap->activated) {
		/* A module probably forgot to set the function pointer */
		(void)pcap_snprintf(pcap->errbuf, sizeof(pcap->errbuf),
		    "This operation isn't properly handled by that device");
		return (PCAP_ERROR);
	}
	/* in case the caller doesn't check for PCAP_ERROR_NOT_ACTIVATED */
	(void)pcap_snprintf(pcap->errbuf, sizeof(pcap->errbuf),
	    "This handle hasn't been activated yet");
	/* this means 'not initialized' */
	return (PCAP_ERROR_NOT_ACTIVATED);
}