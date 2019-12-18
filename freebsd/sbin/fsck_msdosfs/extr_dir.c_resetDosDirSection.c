#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fatEntry {size_t head; int /*<<< orphan*/  flags; } ;
struct bootblock {int bpbRootDirEnts; int bpbSecPerClust; int bpbBytesPerSec; int flags; size_t bpbRootClust; size_t NumClusters; } ;
struct TYPE_4__ {size_t head; } ;

/* Variables and functions */
 size_t CLUST_FIRST ; 
 int FAT32 ; 
 int /*<<< orphan*/  FAT_USED ; 
 int FSFATAL ; 
 int FSOK ; 
 size_t MAX (int,int) ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * delbuf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* newDosDirEntry () ; 
 int /*<<< orphan*/  perr (char*,...) ; 
 int /*<<< orphan*/  pfatal (char*,...) ; 
 TYPE_1__* rootDir ; 

int
resetDosDirSection(struct bootblock *boot, struct fatEntry *fat)
{
	int b1, b2;
	int ret = FSOK;
	size_t len;

	b1 = boot->bpbRootDirEnts * 32;
	b2 = boot->bpbSecPerClust * boot->bpbBytesPerSec;

	if ((buffer = malloc(len = MAX(b1, b2))) == NULL) {
		perr("No space for directory buffer (%zu)", len);
		return FSFATAL;
	}

	if ((delbuf = malloc(len = b2)) == NULL) {
		free(buffer);
		perr("No space for directory delbuf (%zu)", len);
		return FSFATAL;
	}

	if ((rootDir = newDosDirEntry()) == NULL) {
		free(buffer);
		free(delbuf);
		perr("No space for directory entry");
		return FSFATAL;
	}

	memset(rootDir, 0, sizeof *rootDir);
	if (boot->flags & FAT32) {
		if (boot->bpbRootClust < CLUST_FIRST ||
		    boot->bpbRootClust >= boot->NumClusters) {
			pfatal("Root directory starts with cluster out of range(%u)",
			       boot->bpbRootClust);
			return FSFATAL;
		}
		if (fat[boot->bpbRootClust].head != boot->bpbRootClust) {
			pfatal("Root directory doesn't start a cluster chain");
			return FSFATAL;
		}

		fat[boot->bpbRootClust].flags |= FAT_USED;
		rootDir->head = boot->bpbRootClust;
	}

	return ret;
}