#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct fpu_cc_ent {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FPU_KERN_NORMAL ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_kern_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_kern_leave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_fpu_cc_ent (struct fpu_cc_ent*) ; 
 struct fpu_cc_ent* request_fpu_cc_ent () ; 
 int /*<<< orphan*/  x86_64_call1 (void*,int /*<<< orphan*/ ) ; 

uint64_t
_x86_64_call1(void *fn, uint64_t a)
{
	struct fpu_cc_ent *ent;
	uint64_t ret;

	if ((ent = request_fpu_cc_ent()) == NULL)
		return (ENOMEM);
	fpu_kern_enter(curthread, ent->ctx, FPU_KERN_NORMAL);
	ret = x86_64_call1(fn, a);
	fpu_kern_leave(curthread, ent->ctx);
	release_fpu_cc_ent(ent);

	return (ret);
}