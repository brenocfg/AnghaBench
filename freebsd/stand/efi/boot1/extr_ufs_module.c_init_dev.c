#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct disklabel {scalar_t__ d_magic; scalar_t__ d_magic2; TYPE_3__* d_partitions; } ;
struct TYPE_10__ {scalar_t__ partoff; TYPE_2__* dev; } ;
typedef  TYPE_4__ dev_info_t ;
struct TYPE_9__ {scalar_t__ p_offset; } ;
struct TYPE_8__ {TYPE_1__* Media; } ;
struct TYPE_7__ {int BlockSize; } ;

/* Variables and functions */
 int BSD_LABEL_BUFFER ; 
 size_t BSD_LABEL_OFFSET ; 
 scalar_t__ BSD_MAGIC ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  __dmadat ; 
 TYPE_4__* devinfo ; 
 int /*<<< orphan*/ * dmadat ; 
 scalar_t__ dskread (char*,int /*<<< orphan*/ ,int) ; 
 int fsread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_dev(dev_info_t* dev)
{
	char buffer[BSD_LABEL_BUFFER];
	struct disklabel *dl;
	uint64_t bs;
	int ok;

	devinfo = dev;
	dmadat = &__dmadat;

	/*
	 * First try offset 0. This is the typical GPT case where we have no
	 * further partitioning (as well as the degenerate MBR case where
	 * the bsdlabel has a 0 offset).
	 */
	devinfo->partoff = 0;
	ok = fsread(0, NULL, 0);
	if (ok >= 0)
		return (ok);

	/*
	 * Next, we look for a bsdlabel. This is technically located in sector
	 * 1. For 4k sectors, this offset is 4096, for 512b sectors it's
	 * 512. However, we have to fall back to 512 here because we create
	 * images that assume 512 byte blocks, but these can be put on devices
	 * who have 4k (or other) block sizes. If there's a crazy block size, we
	 * skip the 'at one sector' and go stright to checking at 512 bytes.
	 * There are other offsets that are historic, but we don't probe those
	 * since they were never used for MBR disks on FreeBSD on systems that
	 * could boot UEFI. UEFI is little endian only, as are BSD labels. We
	 * will retry fsread(0) only if there's a label found with a non-zero
	 * offset.
	 */
	if (dskread(buffer, 0, BSD_LABEL_BUFFER / DEV_BSIZE) != 0)
		return (-1);
	dl = NULL;
	bs = devinfo->dev->Media->BlockSize;
	if (bs != 0 && bs <= BSD_LABEL_BUFFER / 2)
		dl = (struct disklabel *)&buffer[bs];
	if (dl == NULL || dl->d_magic != BSD_MAGIC || dl->d_magic2 != BSD_MAGIC)
		dl = (struct disklabel *)&buffer[BSD_LABEL_OFFSET];
	if (dl->d_magic != BSD_MAGIC || dl->d_magic2 != BSD_MAGIC ||
	    dl->d_partitions[0].p_offset == 0)
		return (-1);
	devinfo->partoff = dl->d_partitions[0].p_offset;
	return (fsread(0, NULL, 0));
}