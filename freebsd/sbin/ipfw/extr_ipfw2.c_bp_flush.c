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
struct buf_pr {char* ptr; char* buf; int /*<<< orphan*/  size; int /*<<< orphan*/  avail; } ;

/* Variables and functions */

void
bp_flush(struct buf_pr *b)
{

	b->ptr = b->buf;
	b->avail = b->size;
	b->buf[0] = '\0';
}