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
struct bpb {int bpbBytesPerSec; int bpbSecPerClust; int bpbResSectors; int bpbFATs; int bpbRootDirEnts; int bpbSectors; int bpbMedia; int bpbFATsecs; int bpbSecPerTrack; int bpbHeads; int bpbHiddenSecs; int bpbHugeSectors; int bpbBigFATsecs; int bpbRootClust; scalar_t__ bpbFSInfo; scalar_t__ bpbBackup; } ;

/* Variables and functions */
 scalar_t__ MAXU16 ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_bpb(struct bpb *bpb)
{
    printf("BytesPerSec=%u SecPerClust=%u ResSectors=%u FATs=%u",
	   bpb->bpbBytesPerSec, bpb->bpbSecPerClust, bpb->bpbResSectors,
	   bpb->bpbFATs);
    if (bpb->bpbRootDirEnts)
	printf(" RootDirEnts=%u", bpb->bpbRootDirEnts);
    if (bpb->bpbSectors)
	printf(" Sectors=%u", bpb->bpbSectors);
    printf(" Media=%#x", bpb->bpbMedia);
    if (bpb->bpbFATsecs)
	printf(" FATsecs=%u", bpb->bpbFATsecs);
    printf(" SecPerTrack=%u Heads=%u HiddenSecs=%u", bpb->bpbSecPerTrack,
	   bpb->bpbHeads, bpb->bpbHiddenSecs);
    if (bpb->bpbHugeSectors)
	printf(" HugeSectors=%u", bpb->bpbHugeSectors);
    if (!bpb->bpbFATsecs) {
	printf(" FATsecs=%u RootCluster=%u", bpb->bpbBigFATsecs,
	       bpb->bpbRootClust);
	printf(" FSInfo=");
	printf(bpb->bpbFSInfo == MAXU16 ? "%#x" : "%u", bpb->bpbFSInfo);
	printf(" Backup=");
	printf(bpb->bpbBackup == MAXU16 ? "%#x" : "%u", bpb->bpbBackup);
    }
    printf("\n");
}