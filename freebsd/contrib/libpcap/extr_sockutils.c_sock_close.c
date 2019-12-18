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
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_geterror (char*,char*,int) ; 

int sock_close(SOCKET sock, char *errbuf, int errbuflen)
{
	/*
	 * SHUT_WR: subsequent calls to the send function are disallowed.
	 * For TCP sockets, a FIN will be sent after all data is sent and
	 * acknowledged by the Server.
	 */
	if (shutdown(sock, SHUT_WR))
	{
		sock_geterror("shutdown(): ", errbuf, errbuflen);
		/* close the socket anyway */
		closesocket(sock);
		return -1;
	}

	closesocket(sock);
	return 0;
}