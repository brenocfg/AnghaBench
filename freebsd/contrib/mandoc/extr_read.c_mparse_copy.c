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
struct mparse {struct buf* secondary; } ;
struct buf {int /*<<< orphan*/  buf; struct buf* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

void
mparse_copy(const struct mparse *p)
{
	struct buf	*buf;

	for (buf = p->secondary; buf != NULL; buf = buf->next)
		puts(buf->buf);
}