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
struct rpcap_header {int /*<<< orphan*/  plen; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int SOCK_EOF_IS_ERROR ; 
 int SOCK_RECEIVEALL_YES ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int sock_recv (int /*<<< orphan*/ ,char*,int,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcap_recv_msg_header(SOCKET sock, struct rpcap_header *header, char *errbuf)
{
	int nrecv;

	nrecv = sock_recv(sock, (char *) header, sizeof(struct rpcap_header),
	    SOCK_RECEIVEALL_YES|SOCK_EOF_IS_ERROR, errbuf,
	    PCAP_ERRBUF_SIZE);
	if (nrecv == -1)
	{
		/* Network error. */
		return -1;
	}
	header->plen = ntohl(header->plen);
	return 0;
}