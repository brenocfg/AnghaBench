#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct open_disk {int /*<<< orphan*/  table; } ;
struct TYPE_2__ {scalar_t__ d_opendata; } ;
struct disk_devdesc {TYPE_1__ dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,struct open_disk*) ; 
 int /*<<< orphan*/  disk_fmtdev (struct disk_devdesc*) ; 
 int /*<<< orphan*/  free (struct open_disk*) ; 
 int /*<<< orphan*/  ptable_close (int /*<<< orphan*/ ) ; 

int
disk_close(struct disk_devdesc *dev)
{
	struct open_disk *od;

	od = (struct open_disk *)dev->dd.d_opendata;
	DPRINTF("%s closed => %p", disk_fmtdev(dev), od);
	ptable_close(od->table);
	free(od);
	return (0);
}