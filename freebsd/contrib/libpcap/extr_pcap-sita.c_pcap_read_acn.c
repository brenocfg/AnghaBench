#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  unsigned char u_char ;
struct TYPE_7__ {void* tv_usec; void* tv_sec; } ;
struct pcap_pkthdr {int caplen; void* len; TYPE_2__ ts; } ;
struct TYPE_6__ {int /*<<< orphan*/  promisc; int /*<<< orphan*/  timeout; } ;
struct TYPE_8__ {unsigned char* bp; int offset; scalar_t__ buffer; int /*<<< orphan*/  direction; TYPE_1__ opt; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (unsigned char*,struct pcap_pkthdr*,unsigned char*) ;

/* Variables and functions */
 int HEADER_SIZE ; 
 int acn_read_n_bytes_with_timeout (TYPE_3__*,int) ; 
 int /*<<< orphan*/  acn_start_monitor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_read_acn(pcap_t *handle, int max_packets, pcap_handler callback, u_char *user) {
	#define HEADER_SIZE (4 * 4)
	unsigned char		packet_header[HEADER_SIZE];
	struct pcap_pkthdr	pcap_header;

	//printf("pcap_read_acn()\n");			// fulko
	acn_start_monitor(handle->fd, handle->snapshot, handle->opt.timeout, handle->opt.promisc, handle->direction);	/* maybe tell him to start monitoring */
	//printf("pcap_read_acn() after start monitor\n");			// fulko

	handle->bp = packet_header;
	if (acn_read_n_bytes_with_timeout(handle, HEADER_SIZE) == -1) return 0;			/* try to read a packet header in so we can get the sizeof the packet data */

	pcap_header.ts.tv_sec	= ntohl(*(uint32_t *)&packet_header[0]);				/* tv_sec */
	pcap_header.ts.tv_usec	= ntohl(*(uint32_t *)&packet_header[4]);				/* tv_usec */
	pcap_header.caplen		= ntohl(*(uint32_t *)&packet_header[8]);				/* caplen */
	pcap_header.len			= ntohl(*(uint32_t *)&packet_header[12]);				/* len */

	handle->bp = (u_char *)handle->buffer + handle->offset;									/* start off the receive pointer at the right spot */
	if (acn_read_n_bytes_with_timeout(handle, pcap_header.caplen) == -1) return 0;	/* then try to read in the rest of the data */

	callback(user, &pcap_header, handle->bp);										/* call the user supplied callback function */
	return 1;
}