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
struct open_file {TYPE_3__* f_dev; TYPE_2__* f_devdata; } ;
struct geli_devdesc {TYPE_2__* hdesc; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dv_close ) (struct open_file*) ;} ;
struct TYPE_4__ {TYPE_3__* d_dev; } ;
struct TYPE_5__ {TYPE_1__ dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct geli_devdesc*) ; 
 int /*<<< orphan*/  stub1 (struct open_file*) ; 

__attribute__((used)) static int
geli_dev_close(struct open_file *f)
{
	struct geli_devdesc *gdesc;

	/*
	 * Detach the geli_devdesc from the open_file and reattach the
	 * underlying host provider's disk_devdesc; this undoes the work done at
	 * the end of geli_probe_and_attach().  Call the host provider's
	 * dv_close() (because that's what our caller thought it was doing).
	 */
	gdesc = (struct geli_devdesc *)f->f_devdata;
	f->f_devdata = gdesc->hdesc;
	f->f_dev = gdesc->hdesc->dd.d_dev;
	free(gdesc);
	f->f_dev->dv_close(f);
	return (0);
}