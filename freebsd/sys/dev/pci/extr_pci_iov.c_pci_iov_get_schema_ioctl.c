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
struct pci_iov_schema {size_t len; scalar_t__ error; int /*<<< orphan*/  schema; } ;
struct TYPE_4__ {TYPE_1__* iov; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
struct cdev {struct pci_devinfo* si_drv1; } ;
struct TYPE_3__ {int /*<<< orphan*/  iov_schema; } ;

/* Variables and functions */
 scalar_t__ EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_NVLIST ; 
 int copyout (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 void* nvlist_pack (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
pci_iov_get_schema_ioctl(struct cdev *cdev, struct pci_iov_schema *output)
{
	struct pci_devinfo *dinfo;
	void *packed;
	size_t output_len, size;
	int error;

	packed = NULL;

	mtx_lock(&Giant);
	dinfo = cdev->si_drv1;
	packed = nvlist_pack(dinfo->cfg.iov->iov_schema, &size);
	mtx_unlock(&Giant);

	if (packed == NULL) {
		error = ENOMEM;
		goto fail;
	}

	output_len = output->len;
	output->len = size;
	if (size <= output_len) {
		error = copyout(packed, output->schema, size);

		if (error != 0)
			goto fail;

		output->error = 0;
	} else
		/*
		 * If we return an error then the ioctl code won't copyout
		 * output back to userland, so we flag the error in the struct
		 * instead.
		 */
		output->error = EMSGSIZE;

	error = 0;

fail:
	free(packed, M_NVLIST);

	return (error);
}