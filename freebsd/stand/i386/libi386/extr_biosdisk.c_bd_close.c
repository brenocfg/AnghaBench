#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_7__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {TYPE_4__ dd; } ;
struct TYPE_6__ {scalar_t__ bd_open; int /*<<< orphan*/ * bd_bcache; } ;
typedef  TYPE_2__ bdinfo_t ;
struct TYPE_5__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int EIO ; 
 int /*<<< orphan*/  bcache_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* bd_get_bdinfo (TYPE_4__*) ; 
 int disk_close (struct disk_devdesc*) ; 

__attribute__((used)) static int
bd_close(struct open_file *f)
{
	struct disk_devdesc *dev;
	bdinfo_t *bd;
	int rc = 0;

	dev = (struct disk_devdesc *)f->f_devdata;
	bd = bd_get_bdinfo(&dev->dd);
	if (bd == NULL)
		return (EIO);

	bd->bd_open--;
	if (bd->bd_open == 0) {
	    bcache_free(bd->bd_bcache);
	    bd->bd_bcache = NULL;
	}
	if (dev->dd.d_dev->dv_type == DEVT_DISK)
		rc = disk_close(dev);
	return (rc);
}