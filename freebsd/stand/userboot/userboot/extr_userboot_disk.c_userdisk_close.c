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
struct open_file {scalar_t__ f_devdata; } ;
struct TYPE_3__ {size_t d_unit; } ;
struct disk_devdesc {TYPE_1__ dd; } ;
struct TYPE_4__ {scalar_t__ ud_open; int /*<<< orphan*/ * ud_bcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcache_free (int /*<<< orphan*/ *) ; 
 int disk_close (struct disk_devdesc*) ; 
 TYPE_2__* ud_info ; 

__attribute__((used)) static int
userdisk_close(struct open_file *f)
{
	struct disk_devdesc *dev;

	dev = (struct disk_devdesc *)f->f_devdata;
	ud_info[dev->dd.d_unit].ud_open--;
	if (ud_info[dev->dd.d_unit].ud_open == 0) {
		bcache_free(ud_info[dev->dd.d_unit].ud_bcache);
		ud_info[dev->dd.d_unit].ud_bcache = NULL;
	}
	return (disk_close(dev));
}