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
typedef  int /*<<< orphan*/  pcap_if_list_t ;
struct TYPE_3__ {int /*<<< orphan*/  device_code; } ;
typedef  TYPE_1__ dag_card_inf_t ;

/* Variables and functions */
 int DAGNAME_BUFSIZE ; 
 int DAG_MAX_BOARDS ; 
 int DAG_STREAM_MAX ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ dag_attach_stream (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dag_close (int) ; 
 int /*<<< orphan*/  dag_detach_stream (int,int) ; 
 char* dag_device_name (int /*<<< orphan*/ ,int) ; 
 int dag_open (char*) ; 
 int dag_parse_name (char*,char*,int,int*) ; 
 TYPE_1__* dag_pciinfo (int) ; 
 int dag_rx_get_stream_count (int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 

int
dag_findalldevs(pcap_if_list_t *devlistp, char *errbuf)
{
	char name[12];	/* XXX - pick a size */
	int c;
	char dagname[DAGNAME_BUFSIZE];
	int dagstream;
	int dagfd;
	dag_card_inf_t *inf;
	char *description;
	int stream, rxstreams;

	/* Try all the DAGs 0-DAG_MAX_BOARDS */
	for (c = 0; c < DAG_MAX_BOARDS; c++) {
		pcap_snprintf(name, 12, "dag%d", c);
		if (-1 == dag_parse_name(name, dagname, DAGNAME_BUFSIZE, &dagstream))
		{
			(void) pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "dag: device name %s can't be parsed", name);
			return (-1);
		}
		if ( (dagfd = dag_open(dagname)) >= 0 ) {
			description = NULL;
			if ((inf = dag_pciinfo(dagfd)))
				description = dag_device_name(inf->device_code, 1);
			/*
			 * XXX - is there a way to determine whether
			 * the card is plugged into a network or not?
			 * If so, we should check that and set
			 * PCAP_IF_CONNECTION_STATUS_CONNECTED or
			 * PCAP_IF_CONNECTION_STATUS_DISCONNECTED.
			 *
			 * Also, are there notions of "up" and "running"?
			 */
			if (add_dev(devlistp, name, 0, description, errbuf) == NULL) {
				/*
				 * Failure.
				 */
				return (-1);
			}
			rxstreams = dag_rx_get_stream_count(dagfd);
			for(stream=0;stream<DAG_STREAM_MAX;stream+=2) {
				if (0 == dag_attach_stream(dagfd, stream, 0, 0)) {
					dag_detach_stream(dagfd, stream);

					pcap_snprintf(name,  10, "dag%d:%d", c, stream);
					if (add_dev(devlistp, name, 0, description, errbuf) == NULL) {
						/*
						 * Failure.
						 */
						return (-1);
					}

					rxstreams--;
					if(rxstreams <= 0) {
						break;
					}
				}
			}
			dag_close(dagfd);
		}

	}
	return (0);
}