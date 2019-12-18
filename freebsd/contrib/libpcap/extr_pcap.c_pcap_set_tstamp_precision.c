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
typedef  scalar_t__ u_int ;
struct TYPE_5__ {int tstamp_precision; } ;
struct TYPE_6__ {int tstamp_precision_count; scalar_t__* tstamp_precision_list; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int PCAP_ERROR_ACTIVATED ; 
 int PCAP_ERROR_TSTAMP_PRECISION_NOTSUP ; 
 int PCAP_TSTAMP_PRECISION_MICRO ; 
 scalar_t__ pcap_check_activated (TYPE_2__*) ; 

int
pcap_set_tstamp_precision(pcap_t *p, int tstamp_precision)
{
	int i;

	if (pcap_check_activated(p))
		return (PCAP_ERROR_ACTIVATED);

	/*
	 * The argument should have been u_int, but that's too late
	 * to change now - it's an API.
	 */
	if (tstamp_precision < 0)
		return (PCAP_ERROR_TSTAMP_PRECISION_NOTSUP);

	/*
	 * If p->tstamp_precision_count is 0, we only support setting
	 * the time stamp precision to microsecond precision; every
	 * pcap module *MUST* support microsecond precision, even if
	 * it does so by converting the native precision to
	 * microseconds.
	 */
	if (p->tstamp_precision_count == 0) {
		if (tstamp_precision == PCAP_TSTAMP_PRECISION_MICRO) {
			p->opt.tstamp_precision = tstamp_precision;
			return (0);
		}
	} else {
		/*
		 * Check whether we claim to support this precision of
		 * time stamp.
		 */
		for (i = 0; i < p->tstamp_precision_count; i++) {
			if (p->tstamp_precision_list[i] == (u_int)tstamp_precision) {
				/*
				 * Yes.
				 */
				p->opt.tstamp_precision = tstamp_precision;
				return (0);
			}
		}
	}

	/*
	 * We don't support this time stamp precision.
	 */
	return (PCAP_ERROR_TSTAMP_PRECISION_NOTSUP);
}