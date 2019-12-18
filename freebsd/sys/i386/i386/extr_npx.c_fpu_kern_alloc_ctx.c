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
typedef  int u_int ;
struct fpu_kern_ctx {int dummy; } ;

/* Variables and functions */
 int FPU_KERN_NOWAIT ; 
 int /*<<< orphan*/  M_FPUKERN_CTX ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int XSAVE_AREA_ALIGN ; 
 int cpu_max_ext_state_size ; 
 struct fpu_kern_ctx* malloc (size_t,int /*<<< orphan*/ ,int) ; 

struct fpu_kern_ctx *
fpu_kern_alloc_ctx(u_int flags)
{
	struct fpu_kern_ctx *res;
	size_t sz;

	sz = sizeof(struct fpu_kern_ctx) + XSAVE_AREA_ALIGN +
	    cpu_max_ext_state_size;
	res = malloc(sz, M_FPUKERN_CTX, ((flags & FPU_KERN_NOWAIT) ?
	    M_NOWAIT : M_WAITOK) | M_ZERO);
	return (res);
}