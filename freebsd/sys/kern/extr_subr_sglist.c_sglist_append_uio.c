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
struct uio {size_t uio_resid; scalar_t__ uio_segflg; int uio_iovcnt; TYPE_2__* uio_td; struct iovec* uio_iov; } ;
struct sgsave {int dummy; } ;
struct sglist {scalar_t__ sg_maxseg; } ;
struct iovec {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
struct TYPE_4__ {TYPE_1__* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 scalar_t__ UIO_USERSPACE ; 
 int _sglist_append_buf (struct sglist*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmspace_pmap (int /*<<< orphan*/ ) ; 

int
sglist_append_uio(struct sglist *sg, struct uio *uio)
{
	struct iovec *iov;
	struct sgsave save;
	size_t resid, minlen;
	pmap_t pmap;
	int error, i;

	if (sg->sg_maxseg == 0)
		return (EINVAL);

	resid = uio->uio_resid;
	iov = uio->uio_iov;

	if (uio->uio_segflg == UIO_USERSPACE) {
		KASSERT(uio->uio_td != NULL,
		    ("sglist_append_uio: USERSPACE but no thread"));
		pmap = vmspace_pmap(uio->uio_td->td_proc->p_vmspace);
	} else
		pmap = NULL;

	error = 0;
	SGLIST_SAVE(sg, save);
	for (i = 0; i < uio->uio_iovcnt && resid != 0; i++) {
		/*
		 * Now at the first iovec to load.  Load each iovec
		 * until we have exhausted the residual count.
		 */
		minlen = MIN(resid, iov[i].iov_len);
		if (minlen > 0) {
			error = _sglist_append_buf(sg, iov[i].iov_base, minlen,
			    pmap, NULL);
			if (error) {
				SGLIST_RESTORE(sg, save);
				return (error);
			}
			resid -= minlen;
		}
	}
	return (0);
}