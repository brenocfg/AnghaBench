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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct activemap {int am_mediasize; int am_nextents; int am_diskmapsize; int am_syncoff; scalar_t__ am_magic; struct activemap* am_syncmap; struct activemap* am_memmap; struct activemap* am_diskmap; struct activemap* am_memtab; scalar_t__ am_nkeepdirty; int /*<<< orphan*/  am_keepdirty; scalar_t__ am_ndirty; int /*<<< orphan*/  am_mapsize; int /*<<< orphan*/  am_extentshift; scalar_t__ am_extentsize; scalar_t__ am_nkeepdirty_limit; } ;

/* Variables and functions */
 scalar_t__ ACTIVEMAP_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 void* bit_alloc (int) ; 
 int /*<<< orphan*/  bitcount32 (scalar_t__) ; 
 int /*<<< orphan*/  bitstr_size (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct activemap*) ; 
 struct activemap* malloc (int) ; 
 int powerof2 (scalar_t__) ; 
 int roundup2 (int /*<<< orphan*/ ,scalar_t__) ; 

int
activemap_init(struct activemap **ampp, uint64_t mediasize, uint32_t extentsize,
    uint32_t sectorsize, uint32_t keepdirty)
{
	struct activemap *amp;

	PJDLOG_ASSERT(ampp != NULL);
	PJDLOG_ASSERT(mediasize > 0);
	PJDLOG_ASSERT(extentsize > 0);
	PJDLOG_ASSERT(powerof2(extentsize));
	PJDLOG_ASSERT(sectorsize > 0);
	PJDLOG_ASSERT(powerof2(sectorsize));
	PJDLOG_ASSERT(keepdirty > 0);

	amp = malloc(sizeof(*amp));
	if (amp == NULL)
		return (-1);

	amp->am_mediasize = mediasize;
	amp->am_nkeepdirty_limit = keepdirty;
	amp->am_extentsize = extentsize;
	amp->am_extentshift = bitcount32(extentsize - 1);
	amp->am_nextents = ((mediasize - 1) / extentsize) + 1;
	amp->am_mapsize = bitstr_size(amp->am_nextents);
	amp->am_diskmapsize = roundup2(amp->am_mapsize, sectorsize);
	amp->am_ndirty = 0;
	amp->am_syncoff = -2;
	TAILQ_INIT(&amp->am_keepdirty);
	amp->am_nkeepdirty = 0;

	amp->am_memtab = calloc(amp->am_nextents, sizeof(amp->am_memtab[0]));
	amp->am_diskmap = calloc(1, amp->am_diskmapsize);
	amp->am_memmap = bit_alloc(amp->am_nextents);
	amp->am_syncmap = bit_alloc(amp->am_nextents);

	/*
	 * Check to see if any of the allocations above failed.
	 */
	if (amp->am_memtab == NULL || amp->am_diskmap == NULL ||
	    amp->am_memmap == NULL || amp->am_syncmap == NULL) {
		if (amp->am_memtab != NULL)
			free(amp->am_memtab);
		if (amp->am_diskmap != NULL)
			free(amp->am_diskmap);
		if (amp->am_memmap != NULL)
			free(amp->am_memmap);
		if (amp->am_syncmap != NULL)
			free(amp->am_syncmap);
		amp->am_magic = 0;
		free(amp);
		errno = ENOMEM;
		return (-1);
	}

	amp->am_magic = ACTIVEMAP_MAGIC;
	*ampp = amp;

	return (0);
}