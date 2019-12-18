#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dumper; } ;
struct TYPE_6__ {TYPE_1__ di; int /*<<< orphan*/  length; scalar_t__ offset; } ;
struct g_raid_disk {int /*<<< orphan*/  d_softc; int /*<<< orphan*/  d_candelete; TYPE_3__ d_kd; struct g_consumer* d_consumer; } ;
struct g_consumer {TYPE_2__* provider; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFF_MAX ; 
 int g_getattr (char*,struct g_consumer*,int /*<<< orphan*/ *) ; 
 int g_io_getattr (char*,struct g_consumer*,int*,TYPE_3__*) ; 

void
g_raid_get_disk_info(struct g_raid_disk *disk)
{
	struct g_consumer *cp = disk->d_consumer;
	int error, len;

	/* Read kernel dumping information. */
	disk->d_kd.offset = 0;
	disk->d_kd.length = OFF_MAX;
	len = sizeof(disk->d_kd);
	error = g_io_getattr("GEOM::kerneldump", cp, &len, &disk->d_kd);
	if (error)
		disk->d_kd.di.dumper = NULL;
	if (disk->d_kd.di.dumper == NULL)
		G_RAID_DEBUG1(2, disk->d_softc,
		    "Dumping not supported by %s: %d.", 
		    cp->provider->name, error);

	/* Read BIO_DELETE support. */
	error = g_getattr("GEOM::candelete", cp, &disk->d_candelete);
	if (error)
		disk->d_candelete = 0;
	if (!disk->d_candelete)
		G_RAID_DEBUG1(2, disk->d_softc,
		    "BIO_DELETE not supported by %s: %d.", 
		    cp->provider->name, error);
}