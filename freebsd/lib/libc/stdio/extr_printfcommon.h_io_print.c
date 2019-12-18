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
struct TYPE_4__ {size_t uio_iovcnt; int uio_resid; } ;
struct io_state {TYPE_2__ uio; int /*<<< orphan*/  fp; TYPE_1__* iov; } ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_3__ {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 size_t NIOV ; 
 int __sprint (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
io_print(struct io_state *iop, const CHAR * __restrict ptr, int len, locale_t locale)
{

	iop->iov[iop->uio.uio_iovcnt].iov_base = (char *)ptr;
	iop->iov[iop->uio.uio_iovcnt].iov_len = len;
	iop->uio.uio_resid += len;
	if (++iop->uio.uio_iovcnt >= NIOV)
		return (__sprint(iop->fp, &iop->uio, locale));
	else
		return (0);
}