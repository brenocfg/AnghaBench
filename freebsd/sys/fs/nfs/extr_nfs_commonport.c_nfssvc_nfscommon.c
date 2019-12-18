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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nfssvc_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int nfssvc_call (struct thread*,struct nfssvc_args*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfssvc_nfscommon(struct thread *td, struct nfssvc_args *uap)
{
	int error;

	error = nfssvc_call(td, uap, td->td_ucred);
	NFSEXITCODE(error);
	return (error);
}