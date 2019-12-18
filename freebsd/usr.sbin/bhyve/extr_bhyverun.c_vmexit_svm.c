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
struct vmctx {int dummy; } ;
struct TYPE_3__ {int exitcode; int exitinfo1; int exitinfo2; } ;
struct TYPE_4__ {TYPE_1__ svm; } ;
struct vm_exit {int rip; int inst_length; TYPE_2__ u; } ;

/* Variables and functions */
 int VMEXIT_ABORT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
vmexit_svm(struct vmctx *ctx, struct vm_exit *vmexit, int *pvcpu)
{

	fprintf(stderr, "vm exit[%d]\n", *pvcpu);
	fprintf(stderr, "\treason\t\tSVM\n");
	fprintf(stderr, "\trip\t\t0x%016lx\n", vmexit->rip);
	fprintf(stderr, "\tinst_length\t%d\n", vmexit->inst_length);
	fprintf(stderr, "\texitcode\t%#lx\n", vmexit->u.svm.exitcode);
	fprintf(stderr, "\texitinfo1\t%#lx\n", vmexit->u.svm.exitinfo1);
	fprintf(stderr, "\texitinfo2\t%#lx\n", vmexit->u.svm.exitinfo2);
	return (VMEXIT_ABORT);
}