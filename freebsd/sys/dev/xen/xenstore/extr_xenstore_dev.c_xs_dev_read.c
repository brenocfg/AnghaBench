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
struct xs_dev_data {scalar_t__ read_prod; scalar_t__ read_cons; int /*<<< orphan*/ * read_buffer; } ;
struct uio {scalar_t__ uio_resid; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 size_t MASK_READ_IDX (scalar_t__) ; 
 int /*<<< orphan*/  PCATCH ; 
 int devfs_get_cdevpriv (void**) ; 
 int hz ; 
 int tsleep (struct xs_dev_data*,int /*<<< orphan*/ ,char*,int) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int 
xs_dev_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int error;
	struct xs_dev_data *u;

	error = devfs_get_cdevpriv((void **)&u);
	if (error != 0)
		return (error);

	while (u->read_prod == u->read_cons) {
		error = tsleep(u, PCATCH, "xsdread", hz/10);
		if (error && error != EWOULDBLOCK)
			return (error);
	}

	while (uio->uio_resid > 0) {
		if (u->read_cons == u->read_prod)
			break;
		error = uiomove(&u->read_buffer[MASK_READ_IDX(u->read_cons)],
		    1, uio);
		if (error)
			return (error);
		u->read_cons++;
	}
	return (0);
}