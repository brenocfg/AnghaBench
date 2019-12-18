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
struct activemap {scalar_t__ am_magic; size_t am_diskmapsize; scalar_t__ am_diskmap; int /*<<< orphan*/  am_mapsize; int /*<<< orphan*/  am_memmap; } ;

/* Variables and functions */
 scalar_t__ ACTIVEMAP_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  keepdirty_fill (struct activemap*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const unsigned char *
activemap_bitmap(struct activemap *amp, size_t *sizep)
{

	PJDLOG_ASSERT(amp->am_magic == ACTIVEMAP_MAGIC);

	if (sizep != NULL)
		*sizep = amp->am_diskmapsize;
	memcpy(amp->am_diskmap, amp->am_memmap, amp->am_mapsize);
	keepdirty_fill(amp);
	return ((const unsigned char *)amp->am_diskmap);
}