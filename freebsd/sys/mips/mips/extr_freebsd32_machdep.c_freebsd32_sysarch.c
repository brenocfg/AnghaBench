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
typedef  int /*<<< orphan*/  tlsbase ;
struct TYPE_2__ {void* md_tls; } ;
struct thread {TYPE_1__ td_md; } ;
struct freebsd32_sysarch_args {int op; int /*<<< orphan*/  parms; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MIPS_GET_TLS 129 
#define  MIPS_SET_TLS 128 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
freebsd32_sysarch(struct thread *td, struct freebsd32_sysarch_args *uap)
{
	int error;
	int32_t tlsbase;

	switch (uap->op) {
	case MIPS_SET_TLS:
		td->td_md.md_tls = (void *)(intptr_t)uap->parms;
		return (0);
	case MIPS_GET_TLS: 
		tlsbase = (int32_t)(intptr_t)td->td_md.md_tls;
		error = copyout(&tlsbase, uap->parms, sizeof(tlsbase));
		return (error);
	default:
		break;
	}
	return (EINVAL);
}