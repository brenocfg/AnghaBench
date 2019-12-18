#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int daddr_t ;
struct TYPE_4__ {scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/ * gdev; TYPE_2__ dsk; } ;

/* Variables and functions */
 unsigned int DEV_BSIZE ; 
 int drvread (TYPE_2__*,void*,scalar_t__,unsigned int) ; 
 TYPE_1__ gdsk ; 
 scalar_t__ geli_read (int /*<<< orphan*/ *,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int
dskread(void *buf, daddr_t lba, unsigned nblk)
{
	int err;

	err = drvread(&gdsk.dsk, buf, lba + gdsk.dsk.start, nblk);

#ifdef LOADER_GELI_SUPPORT
	if (err == 0 && gdsk.gdev != NULL) {
		/* Decrypt */
		if (geli_read(gdsk.gdev, lba * DEV_BSIZE, buf,
		    nblk * DEV_BSIZE))
			return (err);
	}
#endif

	return (err);
}