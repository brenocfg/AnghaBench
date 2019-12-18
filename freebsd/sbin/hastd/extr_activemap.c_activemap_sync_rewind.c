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
struct activemap {scalar_t__ am_magic; int am_syncoff; int /*<<< orphan*/  am_nextents; int /*<<< orphan*/  am_syncmap; } ;

/* Variables and functions */
 scalar_t__ ACTIVEMAP_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  bit_ffs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
activemap_sync_rewind(struct activemap *amp)
{
	int ext;

	PJDLOG_ASSERT(amp->am_magic == ACTIVEMAP_MAGIC);

	bit_ffs(amp->am_syncmap, amp->am_nextents, &ext);
	if (ext == -1) {
		/* There are no extents to synchronize. */
		amp->am_syncoff = -2;
		return;
	}
	/*
	 * Mark that we want to start synchronization from the beginning.
	 */
	amp->am_syncoff = -1;
}