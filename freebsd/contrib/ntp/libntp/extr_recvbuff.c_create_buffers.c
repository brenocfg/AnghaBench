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
typedef  int /*<<< orphan*/  recvbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int buffer_shortfall ; 
 int /*<<< orphan*/ * eallocarray (int,int) ; 
 int /*<<< orphan*/ * emalloc_zero (int) ; 
 int /*<<< orphan*/  free_recv_list ; 
 int /*<<< orphan*/  free_recvbufs ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  lowater_adds ; 
 int /*<<< orphan*/  total_recvbufs ; 

__attribute__((used)) static void
create_buffers(int nbufs)
{
	register recvbuf_t *bufp;
	int i, abuf;

	abuf = nbufs + buffer_shortfall;
	buffer_shortfall = 0;

#ifndef DEBUG
	bufp = eallocarray(abuf, sizeof(*bufp));
#endif

	for (i = 0; i < abuf; i++) {
#ifdef DEBUG
		/*
		 * Allocate each buffer individually so they can be
		 * free()d during ntpd shutdown on DEBUG builds to
		 * keep them out of heap leak reports.
		 */
		bufp = emalloc_zero(sizeof(*bufp));
#endif
		LINK_SLIST(free_recv_list, bufp, link);
		bufp++;
		free_recvbufs++;
		total_recvbufs++;
	}
	lowater_adds++;
}