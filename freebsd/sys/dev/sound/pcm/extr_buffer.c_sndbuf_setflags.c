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
typedef  int /*<<< orphan*/  u_int32_t ;
struct snd_dbuf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */

void
sndbuf_setflags(struct snd_dbuf *b, u_int32_t flags, int on)
{
	b->flags &= ~flags;
	if (on)
		b->flags |= flags;
}