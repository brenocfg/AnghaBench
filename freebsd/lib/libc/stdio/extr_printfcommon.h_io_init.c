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
struct TYPE_2__ {scalar_t__ uio_iovcnt; scalar_t__ uio_resid; int /*<<< orphan*/  uio_iov; } ;
struct io_state {int /*<<< orphan*/ * fp; TYPE_1__ uio; int /*<<< orphan*/  iov; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

__attribute__((used)) static inline void
io_init(struct io_state *iop, FILE *fp)
{

	iop->uio.uio_iov = iop->iov;
	iop->uio.uio_resid = 0;
	iop->uio.uio_iovcnt = 0;
	iop->fp = fp;
}