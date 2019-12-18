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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  DumpAscii (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EX_OSERR ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsgRead () ; 
 int NG_HOOKSIZ ; 
 int NgAllocRecvData (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  dsock ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
ReadSockets(fd_set *rfds)
{
	/* Display any incoming control message. */
	if (FD_ISSET(csock, rfds))
		MsgRead();

	/* Display any incoming data packet. */
	if (FD_ISSET(dsock, rfds)) {
		char hook[NG_HOOKSIZ];
		u_char *buf;
		int rl;

		/* Read packet from socket. */
		if ((rl = NgAllocRecvData(dsock, &buf, hook)) < 0)
			err(EX_OSERR, "reading hook \"%s\"", hook);
		if (rl == 0)
			errx(EX_OSERR, "EOF from hook \"%s\"?", hook);

		/* Write packet to stdout. */
		printf("Rec'd data packet on hook \"%s\":\n", hook);
		DumpAscii(buf, rl);
		free(buf);
	}
}