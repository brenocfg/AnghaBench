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

/* Variables and functions */
 int /*<<< orphan*/  currenthost ; 
 int debug ; 
 int /*<<< orphan*/  dump_hex_printable (void*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int send (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfd ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sendpkt(
	void *	xdata,
	size_t	xdatalen
	)
{
	if (debug >= 3)
		printf("Sending %zu octets\n", xdatalen);

	if (send(sockfd, xdata, xdatalen, 0) == -1) {
		warning("write to %s failed", currenthost);
		return -1;
	}

	if (debug >= 4) {
		printf("Request packet:\n");
		dump_hex_printable(xdata, xdatalen);
	}
	return 0;
}