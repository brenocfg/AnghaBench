#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t uio_resid; int uio_segflg; int /*<<< orphan*/  uio_rw; } ;
typedef  TYPE_1__ uio_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int UIO_NOCOPY ; 
 int /*<<< orphan*/  uiomove (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
uioskip(uio_t *uio, size_t n)
{
	enum uio_seg segflg;

	/* For the full compatibility with illumos. */
	if (n > uio->uio_resid)
		return;

	segflg = uio->uio_segflg;
	uio->uio_segflg = UIO_NOCOPY;
	uiomove(NULL, n, uio->uio_rw, uio);
	uio->uio_segflg = segflg;
}