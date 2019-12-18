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
struct vmctx {int dummy; } ;
struct TYPE_4__ {int port; int bytes; int in; int /*<<< orphan*/  eax; } ;
struct TYPE_5__ {TYPE_1__ inout; } ;
struct vm_exit {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  rip; } ;

/* Variables and functions */
 int GUEST_NIO_PORT ; 
 int VMEXIT_ABORT ; 
 int VMEXIT_CONTINUE ; 
 int emulate_inout (struct vmctx*,int,struct vm_exit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strictio ; 
 TYPE_3__* vmexit ; 
 int vmexit_handle_notify (struct vmctx*,struct vm_exit*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmexit_inout(struct vmctx *ctx, struct vm_exit *vme, int *pvcpu)
{
	int error;
	int bytes, port, in, out;
	int vcpu;

	vcpu = *pvcpu;

	port = vme->u.inout.port;
	bytes = vme->u.inout.bytes;
	in = vme->u.inout.in;
	out = !in;

        /* Extra-special case of host notifications */
        if (out && port == GUEST_NIO_PORT) {
                error = vmexit_handle_notify(ctx, vme, pvcpu, vme->u.inout.eax);
		return (error);
	}

	error = emulate_inout(ctx, vcpu, vme, strictio);
	if (error) {
		fprintf(stderr, "Unhandled %s%c 0x%04x at 0x%lx\n",
		    in ? "in" : "out",
		    bytes == 1 ? 'b' : (bytes == 2 ? 'w' : 'l'),
		    port, vmexit->rip);
		return (VMEXIT_ABORT);
	} else {
		return (VMEXIT_CONTINUE);
	}
}