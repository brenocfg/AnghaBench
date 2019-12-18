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
struct activemap {scalar_t__ am_magic; int /*<<< orphan*/  am_syncmap; int /*<<< orphan*/  am_memmap; int /*<<< orphan*/  am_diskmap; int /*<<< orphan*/  am_memtab; } ;

/* Variables and functions */
 scalar_t__ ACTIVEMAP_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keepdirty_free (struct activemap*) ; 

void
activemap_free(struct activemap *amp)
{

	PJDLOG_ASSERT(amp->am_magic == ACTIVEMAP_MAGIC);

	amp->am_magic = 0;

	keepdirty_free(amp);
	free(amp->am_memtab);
	free(amp->am_diskmap);
	free(amp->am_memmap);
	free(amp->am_syncmap);
}