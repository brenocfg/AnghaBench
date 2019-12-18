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
struct open_file {TYPE_1__* f_dev; struct devdesc* f_devdata; } ;
struct devdesc {TYPE_1__* d_dev; } ;
struct TYPE_4__ {int (* arch_getdev ) (void**,char const*,char const**) ;} ;
struct TYPE_3__ {int (* dv_open ) (struct open_file*,struct devdesc*) ;scalar_t__ dv_type; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 TYPE_2__ archsw ; 
 int /*<<< orphan*/  free (struct devdesc*) ; 
 int /*<<< orphan*/  geli_probe_and_attach (struct open_file*) ; 
 int stub1 (void**,char const*,char const**) ; 
 int stub2 (struct open_file*,struct devdesc*) ; 

int
devopen(struct open_file *f, const char *fname, const char **file) 
{
	struct devdesc *dev;
	int result;

	result = archsw.arch_getdev((void **)&dev, fname, file);
	if (result)
		return (result);

	/* point to device-specific data so that device open can use it */
	f->f_dev = dev->d_dev;
	f->f_devdata = dev;
	result = dev->d_dev->dv_open(f, dev);
	if (result != 0) {
		f->f_devdata = NULL;
		free(dev);
		return (result);
	}

#ifdef LOADER_GELI_SUPPORT
	/*
	 * If f->f_dev is geli-encrypted and we can decrypt it (will prompt for
	 * pw if needed), this will attach the geli code to the open_file by
	 * replacing f->f_dev and f_devdata with pointers to a geli_devdesc.
	 */
	if (f->f_dev->dv_type == DEVT_DISK) {
		geli_probe_and_attach(f);
	}
#endif

	return (0);
}