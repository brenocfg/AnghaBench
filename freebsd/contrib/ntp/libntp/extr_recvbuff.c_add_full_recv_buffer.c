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
 int /*<<< orphan*/  LINK_FIFO (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  UNLOCK () ; 
 int /*<<< orphan*/  full_recv_fifo ; 
 int /*<<< orphan*/  full_recvbufs ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 

void
add_full_recv_buffer(recvbuf_t *rb)
{
	if (rb == NULL) {
		msyslog(LOG_ERR, "add_full_recv_buffer received NULL buffer");
		return;
	}
	LOCK();
	LINK_FIFO(full_recv_fifo, rb, link);
	full_recvbufs++;
	UNLOCK();
}