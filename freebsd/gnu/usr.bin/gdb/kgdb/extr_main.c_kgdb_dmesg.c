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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int MSGBUF_SEQ_TO_POS (int,int) ; 
 scalar_t__ kgdb_parse (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int) ; 

void
kgdb_dmesg(void)
{
	CORE_ADDR bufp;
	int size, rseq, wseq;
	char c;

	/*
	 * Display the unread portion of the message buffer. This gives the
	 * user a some initial data to work from.
	 */
	if (quiet)
		return;
	bufp = kgdb_parse("msgbufp->msg_ptr");
	size = (int)kgdb_parse("msgbufp->msg_size");
	if (bufp == 0 || size == 0)
		return;
	rseq = (int)kgdb_parse("msgbufp->msg_rseq");
	wseq = (int)kgdb_parse("msgbufp->msg_wseq");
	rseq = MSGBUF_SEQ_TO_POS(size, rseq);
	wseq = MSGBUF_SEQ_TO_POS(size, wseq);
	if (rseq == wseq)
		return;

	printf("\nUnread portion of the kernel message buffer:\n");
	while (rseq < wseq) {
		read_memory(bufp + rseq, &c, 1);
		putchar(c);
		rseq++;
		if (rseq == size)
			rseq = 0;
	}
	if (c != '\n')
		putchar('\n');
	putchar('\n');
}