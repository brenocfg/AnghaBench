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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct g_raid_subdisk {scalar_t__ sd_offset; TYPE_2__* sd_disk; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {scalar_t__ mediaoffset; int /*<<< orphan*/ * dumper; } ;
struct TYPE_4__ {TYPE_3__ di; } ;
struct TYPE_5__ {TYPE_1__ d_kd; } ;

/* Variables and functions */
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int dump_write (TYPE_3__*,void*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 

int
g_raid_subdisk_kerneldump(struct g_raid_subdisk *sd,
    void *virtual, vm_offset_t physical, off_t offset, size_t length)
{

	if (sd->sd_disk == NULL)
		return (ENXIO);
	if (sd->sd_disk->d_kd.di.dumper == NULL)
		return (EOPNOTSUPP);
	return (dump_write(&sd->sd_disk->d_kd.di,
	    virtual, physical,
	    sd->sd_disk->d_kd.di.mediaoffset + sd->sd_offset + offset,
	    length));
}