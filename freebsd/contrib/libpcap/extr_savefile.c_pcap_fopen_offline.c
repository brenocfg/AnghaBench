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
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 int /*<<< orphan*/ * pcap_fopen_offline_with_tstamp_precision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

pcap_t *
pcap_fopen_offline(FILE *fp, char *errbuf)
{
	return (pcap_fopen_offline_with_tstamp_precision(fp,
	    PCAP_TSTAMP_PRECISION_MICRO, errbuf));
}