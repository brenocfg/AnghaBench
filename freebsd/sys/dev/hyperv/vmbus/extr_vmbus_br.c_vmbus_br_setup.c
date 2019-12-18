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
struct vmbus_bufring {int dummy; } ;
struct vmbus_br {int vbr_dsize; void* vbr; } ;

/* Variables and functions */

__attribute__((used)) static void
vmbus_br_setup(struct vmbus_br *br, void *buf, int blen)
{
	br->vbr = buf;
	br->vbr_dsize = blen - sizeof(struct vmbus_bufring);
}