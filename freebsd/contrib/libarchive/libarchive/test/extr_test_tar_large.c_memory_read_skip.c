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
struct memdata {scalar_t__ filebytes; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
memory_read_skip(struct archive *a, void *_private, int64_t skip)
{
	struct memdata *private = _private;

	(void)a;

	if (private->first == NULL) {
		private->last = NULL;
		return (0);
	}
	if (private->filebytes > 0) {
		if (private->filebytes < skip)
			skip = (off_t)private->filebytes;
		private->filebytes -= skip;
	} else {
		skip = 0;
	}
	return (skip);
}