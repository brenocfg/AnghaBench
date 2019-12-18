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
struct open_file {scalar_t__ f_devdata; } ;
struct disk_devdesc {int dummy; } ;

/* Variables and functions */
 int disk_close (struct disk_devdesc*) ; 

__attribute__((used)) static int
beri_sdcard_disk_close(struct open_file *f)
{
	struct disk_devdesc *dev;

	dev = (struct disk_devdesc *)f->f_devdata;
	return (disk_close(dev));
}