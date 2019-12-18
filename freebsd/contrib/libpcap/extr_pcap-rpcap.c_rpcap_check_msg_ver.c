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
typedef  scalar_t__ uint8 ;
struct rpcap_header {scalar_t__ ver; int /*<<< orphan*/  plen; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int rpcap_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rpcap_check_msg_ver(SOCKET sock, uint8 expected_ver, struct rpcap_header *header, char *errbuf)
{
	/*
	 * Did the server specify the version we negotiated?
	 */
	if (header->ver != expected_ver)
	{
		/*
		 * Discard the rest of the message.
		 */
		if (rpcap_discard(sock, header->plen, errbuf) == -1)
			return -1;

		/*
		 * Tell our caller that it's not the negotiated version.
		 */
		if (errbuf != NULL)
		{
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "Server sent us a message with version %u when we were expecting %u",
			    header->ver, expected_ver);
		}
		return -1;
	}
	return 0;
}