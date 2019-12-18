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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int PCAP_ERRBUF_SIZE ; 
 int SOCK_EOF_IS_ERROR ; 
 int SOCK_RECEIVEALL_YES ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  rpcap_discard (int /*<<< orphan*/ ,int,char*) ; 
 int sock_recv (int /*<<< orphan*/ ,char*,int,int,char*,int) ; 

__attribute__((used)) static void rpcap_msg_err(SOCKET sockctrl, uint32 plen, char *remote_errbuf)
{
	char errbuf[PCAP_ERRBUF_SIZE];

	if (plen >= PCAP_ERRBUF_SIZE)
	{
		/*
		 * Message is too long; just read as much of it as we
		 * can into the buffer provided, and discard the rest.
		 */
		if (sock_recv(sockctrl, remote_errbuf, PCAP_ERRBUF_SIZE - 1,
		    SOCK_RECEIVEALL_YES|SOCK_EOF_IS_ERROR, errbuf,
		    PCAP_ERRBUF_SIZE) == -1)
		{
			// Network error.
			pcap_snprintf(remote_errbuf, PCAP_ERRBUF_SIZE, "Read of error message from client failed: %s", errbuf);
			return;
		}

		/*
		 * Null-terminate it.
		 */
		remote_errbuf[PCAP_ERRBUF_SIZE - 1] = '\0';

		/*
		 * Throw away the rest.
		 */
		(void)rpcap_discard(sockctrl, plen - (PCAP_ERRBUF_SIZE - 1), remote_errbuf);
	}
	else if (plen == 0)
	{
		/* Empty error string. */
		remote_errbuf[0] = '\0';
	}
	else
	{
		if (sock_recv(sockctrl, remote_errbuf, plen,
		    SOCK_RECEIVEALL_YES|SOCK_EOF_IS_ERROR, errbuf,
		    PCAP_ERRBUF_SIZE) == -1)
		{
			// Network error.
			pcap_snprintf(remote_errbuf, PCAP_ERRBUF_SIZE, "Read of error message from client failed: %s", errbuf);
			return;
		}

		/*
		 * Null-terminate it.
		 */
		remote_errbuf[plen] = '\0';
	}
}