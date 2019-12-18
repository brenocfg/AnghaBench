#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ recvbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK () ; 
 int /*<<< orphan*/  UNLINK_HEAD_SLIST (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK () ; 
 int /*<<< orphan*/  buffer_shortfall ; 
 int /*<<< orphan*/  free_recv_list ; 
 int /*<<< orphan*/  free_recvbufs ; 
 int /*<<< orphan*/  initialise_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  link ; 

recvbuf_t *
get_free_recv_buffer(void)
{
	recvbuf_t *buffer;

	LOCK();
	UNLINK_HEAD_SLIST(buffer, free_recv_list, link);
	if (buffer != NULL) {
		free_recvbufs--;
		initialise_buffer(buffer);
		buffer->used++;
	} else {
		buffer_shortfall++;
	}
	UNLOCK();

	return buffer;
}