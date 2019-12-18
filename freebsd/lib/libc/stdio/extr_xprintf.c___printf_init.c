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
struct TYPE_2__ {scalar_t__ uio_iovcnt; scalar_t__ uio_resid; int /*<<< orphan*/ * uio_iov; } ;
struct __printf_io {TYPE_1__ uio; int /*<<< orphan*/ * iov; int /*<<< orphan*/ * iovp; } ;

/* Variables and functions */

__attribute__((used)) static void
__printf_init(struct __printf_io *io)
{

	io->uio.uio_iov = io->iovp = &io->iov[0];
	io->uio.uio_resid = 0;
	io->uio.uio_iovcnt = 0;
}