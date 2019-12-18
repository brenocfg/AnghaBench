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
struct uio {int uio_iovcnt; size_t uio_resid; TYPE_1__* uio_iov; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; } ;
struct thread {int dummy; } ;
struct csession {int dummy; } ;
struct cryptop_data {TYPE_1__* iovec; struct uio uio; struct csession* cse; } ;
struct TYPE_2__ {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XDATA ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cryptop_data *
cod_alloc(struct csession *cse, size_t len, struct thread *td)
{
	struct cryptop_data *cod;
	struct uio *uio;

	cod = malloc(sizeof(struct cryptop_data), M_XDATA, M_WAITOK | M_ZERO);

	cod->cse = cse;
	uio = &cod->uio;
	uio->uio_iov = cod->iovec;
	uio->uio_iovcnt = 1;
	uio->uio_resid = len;
	uio->uio_segflg = UIO_SYSSPACE;
	uio->uio_rw = UIO_WRITE;
	uio->uio_td = td;
	uio->uio_iov[0].iov_len = len;
	uio->uio_iov[0].iov_base = malloc(len, M_XDATA, M_WAITOK);
	return (cod);
}