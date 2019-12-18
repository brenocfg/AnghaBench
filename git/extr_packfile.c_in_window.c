#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pack_window {scalar_t__ offset; scalar_t__ len; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int in_window(struct pack_window *win, off_t offset)
{
	/* We must promise at least one full hash after the
	 * offset is available from this window, otherwise the offset
	 * is not actually in this window and a different window (which
	 * has that one hash excess) must be used.  This is to support
	 * the object header and delta base parsing routines below.
	 */
	off_t win_off = win->offset;
	return win_off <= offset
		&& (offset + the_hash_algo->rawsz) <= (win_off + win->len);
}