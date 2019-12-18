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
struct fileblocks {TYPE_1__* current; int /*<<< orphan*/  gap_remaining; int /*<<< orphan*/  buff; scalar_t__ fileposition; TYPE_1__* first; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gap_size; int /*<<< orphan*/  buff; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
memory_read_open(struct archive *a, void *_private)
{
	struct fileblocks *private = _private;

	(void)a; /* UNUSED */

	private->current = private->first;
	private->fileposition = 0;
	if (private->current != NULL) {
		private->buff = private->current->buff;
		private->gap_remaining = private->current->gap_size;
	}
	return (ARCHIVE_OK);
}