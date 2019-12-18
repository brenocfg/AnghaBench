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
 int /*<<< orphan*/  SOCK_DEBUG_MESSAGE (char*) ; 
 int /*<<< orphan*/  SOCK_RECEIVEALL_YES ; 
 int TEMP_BUF_SIZE ; 
 int sock_recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*,int) ; 

int sock_discard(SOCKET sock, int size, char *errbuf, int errbuflen)
{
#define TEMP_BUF_SIZE 32768

	char buffer[TEMP_BUF_SIZE];		/* network buffer, to be used when the message is discarded */

	/*
	 * A static allocation avoids the need of a 'malloc()' each time we want to discard a message
	 * Our feeling is that a buffer if 32KB is enough for most of the application;
	 * in case this is not enough, the "while" loop discards the message by calling the
	 * sockrecv() several times.
	 * We do not want to create a bigger variable because this causes the program to exit on
	 * some platforms (e.g. BSD)
	 */
	while (size > TEMP_BUF_SIZE)
	{
		if (sock_recv(sock, buffer, TEMP_BUF_SIZE, SOCK_RECEIVEALL_YES, errbuf, errbuflen) == -1)
			return -1;

		size -= TEMP_BUF_SIZE;
	}

	/*
	 * If there is still data to be discarded
	 * In this case, the data can fit into the temporary buffer
	 */
	if (size)
	{
		if (sock_recv(sock, buffer, size, SOCK_RECEIVEALL_YES, errbuf, errbuflen) == -1)
			return -1;
	}

	SOCK_DEBUG_MESSAGE("I'm currently discarding data\n");

	return 0;
}