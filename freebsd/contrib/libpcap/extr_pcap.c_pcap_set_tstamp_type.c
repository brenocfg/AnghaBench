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
struct TYPE_5__ {int tstamp_type; } ;
struct TYPE_6__ {int tstamp_type_count; scalar_t__* tstamp_type_list; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int PCAP_ERROR_ACTIVATED ; 
 int PCAP_TSTAMP_HOST ; 
 int PCAP_WARNING_TSTAMP_TYPE_NOTSUP ; 
 scalar_t__ pcap_check_activated (TYPE_2__*) ; 

int
pcap_set_tstamp_type(pcap_t *p, int tstamp_type)
{
	int i;

	if (pcap_check_activated(p))
		return (PCAP_ERROR_ACTIVATED);

	/*
	 * The argument should have been u_int, but that's too late
	 * to change now - it's an API.
	 */
	if (tstamp_type < 0)
		return (PCAP_WARNING_TSTAMP_TYPE_NOTSUP);

	/*
	 * If p->tstamp_type_count is 0, we only support PCAP_TSTAMP_HOST;
	 * the default time stamp type is PCAP_TSTAMP_HOST.
	 */
	if (p->tstamp_type_count == 0) {
		if (tstamp_type == PCAP_TSTAMP_HOST) {
			p->opt.tstamp_type = tstamp_type;
			return (0);
		}
	} else {
		/*
		 * Check whether we claim to support this type of time stamp.
		 */
		for (i = 0; i < p->tstamp_type_count; i++) {
			if (p->tstamp_type_list[i] == (u_int)tstamp_type) {
				/*
				 * Yes.
				 */
				p->opt.tstamp_type = tstamp_type;
				return (0);
			}
		}
	}

	/*
	 * We don't support this type of time stamp.
	 */
	return (PCAP_WARNING_TSTAMP_TYPE_NOTSUP);
}