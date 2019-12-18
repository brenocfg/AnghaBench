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
struct io_buffer {scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_buffer_advance (struct io_buffer*,size_t) ; 
 int /*<<< orphan*/  io_buffer_head (struct io_buffer*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
io_buffer_consume(struct io_buffer *io, size_t amount)
{

	io_buffer_advance(io, amount);
	if (io->len == 0) {
		io->start = 0;
		return;
	}

	/*
	 * XXX: Consider making this move optional and compacting on a
	 * future read() before realloc().
	 */
	memmove(io->data, io_buffer_head(io), io->len);
	io->start = 0;
}