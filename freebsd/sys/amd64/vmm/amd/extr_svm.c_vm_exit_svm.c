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
typedef  void* uint64_t ;
struct TYPE_3__ {void* exitinfo2; void* exitinfo1; void* exitcode; } ;
struct TYPE_4__ {TYPE_1__ svm; } ;
struct vm_exit {TYPE_2__ u; int /*<<< orphan*/  exitcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_EXITCODE_SVM ; 

__attribute__((used)) static void
vm_exit_svm(struct vm_exit *vme, uint64_t code, uint64_t info1, uint64_t info2)
{

	vme->exitcode = VM_EXITCODE_SVM;
	vme->u.svm.exitcode = code;
	vme->u.svm.exitinfo1 = info1;
	vme->u.svm.exitinfo2 = info2;
}