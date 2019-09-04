#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long next_in; unsigned long next_out; scalar_t__ total_out; scalar_t__ total_in; } ;
struct TYPE_5__ {unsigned long next_in; unsigned long next_out; scalar_t__ total_out; scalar_t__ total_in; unsigned long avail_in; unsigned long avail_out; TYPE_1__ z; } ;
typedef  TYPE_2__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 

__attribute__((used)) static void zlib_post_call(git_zstream *s)
{
	unsigned long bytes_consumed;
	unsigned long bytes_produced;

	bytes_consumed = s->z.next_in - s->next_in;
	bytes_produced = s->z.next_out - s->next_out;
	if (s->z.total_out != s->total_out + bytes_produced)
		BUG("total_out mismatch");
	if (s->z.total_in != s->total_in + bytes_consumed)
		BUG("total_in mismatch");

	s->total_out = s->z.total_out;
	s->total_in = s->z.total_in;
	s->next_in = s->z.next_in;
	s->next_out = s->z.next_out;
	s->avail_in -= bytes_consumed;
	s->avail_out -= bytes_produced;
}