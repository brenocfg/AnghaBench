#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct TYPE_7__ {TYPE_2__* dev; scalar_t__ partoff; } ;
struct TYPE_6__ {scalar_t__ (* ReadBlocks ) (TYPE_2__*,int /*<<< orphan*/ ,int,int,void*) ;TYPE_1__* Media; } ;
struct TYPE_5__ {int BlockSize; int /*<<< orphan*/  MediaId; } ;
typedef  scalar_t__ EFI_STATUS ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DPRINTF (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (scalar_t__) ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_3__* devinfo ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int,void*) ; 

__attribute__((used)) static int
dskread(void *buf, uint64_t lba, int nblk)
{
	int size;
	EFI_STATUS status;

	lba += devinfo->partoff;
	lba = lba / (devinfo->dev->Media->BlockSize / DEV_BSIZE);
	size = nblk * DEV_BSIZE;

	status = devinfo->dev->ReadBlocks(devinfo->dev,
	    devinfo->dev->Media->MediaId, lba, size, buf);

	if (status != EFI_SUCCESS) {
		DPRINTF("dskread: failed dev: %p, id: %u, lba: %ju, size: %d, "
		    "status: %lu\n", devinfo->dev,
		    devinfo->dev->Media->MediaId, (uintmax_t)lba, size,
		    EFI_ERROR_CODE(status));
		return (-1);
	}

	return (0);
}