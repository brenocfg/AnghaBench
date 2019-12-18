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
struct lzh_stream {int avail_out; size_t total_out; TYPE_1__* ds; int /*<<< orphan*/  ref_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  w_buff; } ;

/* Variables and functions */

__attribute__((used)) static void
lzh_emit_window(struct lzh_stream *strm, size_t s)
{
	strm->ref_ptr = strm->ds->w_buff;
	strm->avail_out = (int)s;
	strm->total_out += s;
}