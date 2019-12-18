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
typedef  int uint64_t ;
struct xstate_hdr {int xstate_bv; } ;
struct thread {int dummy; } ;
struct savefpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int cpu_max_ext_state_size ; 
 scalar_t__ get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  use_xsave ; 
 int xsave_mask ; 

int
fpusetxstate(struct thread *td, char *xfpustate, size_t xfpustate_size)
{
	struct xstate_hdr *hdr, *ehdr;
	size_t len, max_len;
	uint64_t bv;

	/* XXXKIB should we clear all extended state in xstate_bv instead ? */
	if (xfpustate == NULL)
		return (0);
	if (!use_xsave)
		return (EOPNOTSUPP);

	len = xfpustate_size;
	if (len < sizeof(struct xstate_hdr))
		return (EINVAL);
	max_len = cpu_max_ext_state_size - sizeof(struct savefpu);
	if (len > max_len)
		return (EINVAL);

	ehdr = (struct xstate_hdr *)xfpustate;
	bv = ehdr->xstate_bv;

	/*
	 * Avoid #gp.
	 */
	if (bv & ~xsave_mask)
		return (EINVAL);

	hdr = (struct xstate_hdr *)(get_pcb_user_save_td(td) + 1);

	hdr->xstate_bv = bv;
	bcopy(xfpustate + sizeof(struct xstate_hdr),
	    (char *)(hdr + 1), len - sizeof(struct xstate_hdr));

	return (0);
}