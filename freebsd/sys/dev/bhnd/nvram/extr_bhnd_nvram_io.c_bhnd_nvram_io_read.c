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
struct bhnd_nvram_io {TYPE_1__* iops; } ;
struct TYPE_2__ {int (* read ) (struct bhnd_nvram_io*,size_t,void*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct bhnd_nvram_io*,size_t,void*,size_t) ; 

int
bhnd_nvram_io_read(struct bhnd_nvram_io *io, size_t offset, void *buffer,
    size_t nbytes)
{
	return (io->iops->read(io, offset, buffer, nbytes));
}