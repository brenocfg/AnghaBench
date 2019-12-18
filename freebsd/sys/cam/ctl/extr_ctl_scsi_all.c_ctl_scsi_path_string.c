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
struct TYPE_4__ {int initid; int targ_port; int targ_lun; int targ_mapped_lun; } ;
struct TYPE_3__ {TYPE_2__ nexus; } ;
union ctl_io {TYPE_1__ io_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

void
ctl_scsi_path_string(union ctl_io *io, char *path_str, int len)
{

	snprintf(path_str, len, "(%u:%u:%u/%u): ",
	    io->io_hdr.nexus.initid, io->io_hdr.nexus.targ_port,
	    io->io_hdr.nexus.targ_lun, io->io_hdr.nexus.targ_mapped_lun);
}