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
typedef  scalar_t__ u_int ;
struct TYPE_4__ {int dlt_count; int (* set_datalink_op ) (TYPE_1__*,int) ;int linktype; scalar_t__* dlt_list; int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int DLT_DOCSIS ; 
 scalar_t__ DLT_EN10MB ; 
 char* pcap_datalink_val_to_name (int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int stub1 (TYPE_1__*,int) ; 

int
pcap_set_datalink(pcap_t *p, int dlt)
{
	int i;
	const char *dlt_name;

	if (dlt < 0)
		goto unsupported;

	if (p->dlt_count == 0 || p->set_datalink_op == NULL) {
		/*
		 * We couldn't fetch the list of DLTs, or we don't
		 * have a "set datalink" operation, which means
		 * this platform doesn't support changing the
		 * DLT for an interface.  Check whether the new
		 * DLT is the one this interface supports.
		 */
		if (p->linktype != dlt)
			goto unsupported;

		/*
		 * It is, so there's nothing we need to do here.
		 */
		return (0);
	}
	for (i = 0; i < p->dlt_count; i++)
		if (p->dlt_list[i] == (u_int)dlt)
			break;
	if (i >= p->dlt_count)
		goto unsupported;
	if (p->dlt_count == 2 && p->dlt_list[0] == DLT_EN10MB &&
	    dlt == DLT_DOCSIS) {
		/*
		 * This is presumably an Ethernet device, as the first
		 * link-layer type it offers is DLT_EN10MB, and the only
		 * other type it offers is DLT_DOCSIS.  That means that
		 * we can't tell the driver to supply DOCSIS link-layer
		 * headers - we're just pretending that's what we're
		 * getting, as, presumably, we're capturing on a dedicated
		 * link to a Cisco Cable Modem Termination System, and
		 * it's putting raw DOCSIS frames on the wire inside low-level
		 * Ethernet framing.
		 */
		p->linktype = dlt;
		return (0);
	}
	if (p->set_datalink_op(p, dlt) == -1)
		return (-1);
	p->linktype = dlt;
	return (0);

unsupported:
	dlt_name = pcap_datalink_val_to_name(dlt);
	if (dlt_name != NULL) {
		(void) pcap_snprintf(p->errbuf, sizeof(p->errbuf),
		    "%s is not one of the DLTs supported by this device",
		    dlt_name);
	} else {
		(void) pcap_snprintf(p->errbuf, sizeof(p->errbuf),
		    "DLT %d is not one of the DLTs supported by this device",
		    dlt);
	}
	return (-1);
}