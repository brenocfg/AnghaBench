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
struct TYPE_5__ {int /*<<< orphan*/  vp; } ;
struct TYPE_4__ {int (* doio ) (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ;int /*<<< orphan*/  fp; } ;
struct TYPE_6__ {TYPE_2__ vop_args; TYPE_1__ fop_args; } ;
struct vn_io_fault_args {int kind; int /*<<< orphan*/  cred; int /*<<< orphan*/  flags; TYPE_3__ args; } ;
struct uio {int /*<<< orphan*/  uio_rw; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_WRITE ; 
#define  VN_IO_FAULT_FOP 129 
#define  VN_IO_FAULT_VOP 128 
 int VOP_READ (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VOP_WRITE (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int vm_fault_disable_pagefaults () ; 
 int /*<<< orphan*/  vm_fault_enable_pagefaults (int) ; 

__attribute__((used)) static int
vn_io_fault_doio(struct vn_io_fault_args *args, struct uio *uio,
    struct thread *td)
{
	int error, save;

	error = 0;
	save = vm_fault_disable_pagefaults();
	switch (args->kind) {
	case VN_IO_FAULT_FOP:
		error = (args->args.fop_args.doio)(args->args.fop_args.fp,
		    uio, args->cred, args->flags, td);
		break;
	case VN_IO_FAULT_VOP:
		if (uio->uio_rw == UIO_READ) {
			error = VOP_READ(args->args.vop_args.vp, uio,
			    args->flags, args->cred);
		} else if (uio->uio_rw == UIO_WRITE) {
			error = VOP_WRITE(args->args.vop_args.vp, uio,
			    args->flags, args->cred);
		}
		break;
	default:
		panic("vn_io_fault_doio: unknown kind of io %d %d",
		    args->kind, uio->uio_rw);
	}
	vm_fault_enable_pagefaults(save);
	return (error);
}