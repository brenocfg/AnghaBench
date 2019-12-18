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
struct event_overlapped {int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  iocp_callback ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct event_overlapped*,int /*<<< orphan*/ ,int) ; 

void
event_overlapped_init_(struct event_overlapped *o, iocp_callback cb)
{
	memset(o, 0, sizeof(struct event_overlapped));
	o->cb = cb;
}