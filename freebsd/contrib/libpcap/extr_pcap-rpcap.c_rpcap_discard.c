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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int sock_discard (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcap_discard(SOCKET sock, uint32 len, char *errbuf)
{
	if (len != 0)
	{
		if (sock_discard(sock, len, errbuf, PCAP_ERRBUF_SIZE) == -1)
		{
			// Network error.
			return -1;
		}
	}
	return 0;
}