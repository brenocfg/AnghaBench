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
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int SOCK_EOF_IS_ERROR ; 
 int SOCK_RECEIVEALL_YES ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int sock_recv (int /*<<< orphan*/ ,void*,size_t,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcap_recv(SOCKET sock, void *buffer, size_t toread, uint32 *plen, char *errbuf)
{
	int nread;

	if (toread > *plen)
	{
		/* The server sent us a bad message */
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Message payload is too short");
		return -1;
	}
	nread = sock_recv(sock, buffer, toread,
	    SOCK_RECEIVEALL_YES|SOCK_EOF_IS_ERROR, errbuf, PCAP_ERRBUF_SIZE);
	if (nread == -1)
	{
		return -1;
	}
	*plen -= nread;
	return 0;
}