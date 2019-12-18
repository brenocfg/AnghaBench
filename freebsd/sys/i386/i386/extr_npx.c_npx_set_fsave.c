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
union savefpu {int /*<<< orphan*/  sv_xmm; } ;
typedef  int /*<<< orphan*/  sv ;
struct fpacc87 {int dummy; } ;
struct env87 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,union savefpu*,int) ; 
 int /*<<< orphan*/  bzero (union savefpu*,int) ; 
 scalar_t__ cpu_fxsr ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  npx_set_fpregs_xmm (void*,int /*<<< orphan*/ *) ; 
 int npxsetregs (int /*<<< orphan*/ ,union savefpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
npx_set_fsave(void *addr)
{
	union savefpu sv;
	int error;

	bzero(&sv, sizeof(sv));
	if (cpu_fxsr)
		npx_set_fpregs_xmm(addr, &sv.sv_xmm);
	else
		bcopy(addr, &sv, sizeof(struct env87) +
		    sizeof(struct fpacc87[8]));
	error = npxsetregs(curthread, &sv, NULL, 0);
	return (error);
}