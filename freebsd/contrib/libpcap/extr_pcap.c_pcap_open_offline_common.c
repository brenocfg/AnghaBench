#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tstamp_precision; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 TYPE_2__* pcap_alloc_pcap_t (char*,size_t) ; 

pcap_t *
pcap_open_offline_common(char *ebuf, size_t size)
{
	pcap_t *p;

	p = pcap_alloc_pcap_t(ebuf, size);
	if (p == NULL)
		return (NULL);

	p->opt.tstamp_precision = PCAP_TSTAMP_PRECISION_MICRO;

	return (p);
}