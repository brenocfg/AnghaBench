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
struct TYPE_3__ {int dlt_count; int linktype; int /*<<< orphan*/  dlt_list; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  activated; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int PCAP_ERROR ; 
 int PCAP_ERROR_NOT_ACTIVATED ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 

int
pcap_list_datalinks(pcap_t *p, int **dlt_buffer)
{
	if (!p->activated)
		return (PCAP_ERROR_NOT_ACTIVATED);
	if (p->dlt_count == 0) {
		/*
		 * We couldn't fetch the list of DLTs, which means
		 * this platform doesn't support changing the
		 * DLT for an interface.  Return a list of DLTs
		 * containing only the DLT this device supports.
		 */
		*dlt_buffer = (int*)malloc(sizeof(**dlt_buffer));
		if (*dlt_buffer == NULL) {
			pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
			    errno, "malloc");
			return (PCAP_ERROR);
		}
		**dlt_buffer = p->linktype;
		return (1);
	} else {
		*dlt_buffer = (int*)calloc(sizeof(**dlt_buffer), p->dlt_count);
		if (*dlt_buffer == NULL) {
			pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
			    errno, "malloc");
			return (PCAP_ERROR);
		}
		(void)memcpy(*dlt_buffer, p->dlt_list,
		    sizeof(**dlt_buffer) * p->dlt_count);
		return (p->dlt_count);
	}
}