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
struct read_memory_data {int end; int p; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
memory_read_skip(struct archive *a, void *client_data, int64_t skip)
{
	struct read_memory_data *mine = (struct read_memory_data *)client_data;

	(void)a; /* UNUSED */
	/* We can't skip by more than is available. */
	if ((off_t)skip > (off_t)(mine->end - mine->p))
		skip = mine->end - mine->p;
	/* Always do small skips by prime amounts. */
	if (skip > 71)
		skip = 71;
	mine->p += skip;
	return (skip);
}