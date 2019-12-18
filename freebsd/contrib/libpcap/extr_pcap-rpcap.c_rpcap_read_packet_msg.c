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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int cc; int /*<<< orphan*/ * bp; int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int SOCK_EOF_IS_ERROR ; 
 int SOCK_RECEIVEALL_NO ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int sock_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcap_read_packet_msg(SOCKET sock, pcap_t *p, size_t size)
{
	u_char *bp;
	int cc;
	int bytes_read;

	bp = p->bp;
	cc = p->cc;

	/*
	 * Loop until we have the amount of data requested or we get
	 * an error or interrupt.
	 */
	while ((size_t)cc < size)
	{
		/*
		 * We haven't read all of the packet header yet.
		 * Read what remains, which could be all of it.
		 */
		bytes_read = sock_recv(sock, bp, size - cc,
		    SOCK_RECEIVEALL_NO|SOCK_EOF_IS_ERROR, p->errbuf,
		    PCAP_ERRBUF_SIZE);
		if (bytes_read == -1)
		{
			/*
			 * Network error.  Update the read pointer and
			 * byte count, and return an error indication.
			 */
			p->bp = bp;
			p->cc = cc;
			return -1;
		}
		if (bytes_read == -3)
		{
			/*
			 * Interrupted receive.  Update the read
			 * pointer and byte count, and return
			 * an interrupted indication.
			 */
			p->bp = bp;
			p->cc = cc;
			return -3;
		}
		if (bytes_read == 0)
		{
			/*
			 * EOF - server terminated the connection.
			 * Update the read pointer and byte count, and
			 * return an error indication.
			 */
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "The server terminated the connection.");
			return -1;
		}
		bp += bytes_read;
		cc += bytes_read;
	}
	p->bp = bp;
	p->cc = cc;
	return 0;
}