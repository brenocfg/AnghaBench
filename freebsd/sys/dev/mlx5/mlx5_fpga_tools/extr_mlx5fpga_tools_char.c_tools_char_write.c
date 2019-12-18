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
typedef  int /*<<< orphan*/  uintmax_t ;
struct uio {size_t uio_resid; scalar_t__ uio_offset; } ;
struct tools_context {int /*<<< orphan*/  access_type; TYPE_1__* tdev; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int /*<<< orphan*/  fdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mem_write (TYPE_1__*,void*,size_t,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mlx5_fpga_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tools_char_llseek (struct tools_context*,struct uio*,size_t*) ; 
 int uiomove (void*,size_t,struct uio*) ; 

__attribute__((used)) static int
tools_char_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct tools_context *context;
	void *kbuf;
	off_t of;
	size_t len, len1;
	int ret;

	ret = devfs_get_cdevpriv((void **)&context);
	if (ret != 0)
		return (ret);
	dev_dbg(mlx5_fpga_dev(context->tdev->fdev),
	    "tools char device reading %zu bytes at 0x%jx\n", uio->uio_resid,
	    (uintmax_t)uio->uio_offset);

	tools_char_llseek(context, uio, &len);
	if (len == 0)
		return (0);

	kbuf = malloc(len, M_DEVBUF, M_WAITOK);
	len1 = uio->uio_resid;
	of = uio->uio_offset;

	ret = uiomove(kbuf, len, uio);
	if (ret == 0) {
		len1 -= uio->uio_resid;
		ret = mem_write(context->tdev, kbuf, len, of,
		    context->access_type, &len1);
	}
	free(kbuf, M_DEVBUF);
	return (ret);
}