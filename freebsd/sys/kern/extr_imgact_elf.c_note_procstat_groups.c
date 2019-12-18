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
typedef  int /*<<< orphan*/  structsize ;
struct sbuf {int dummy; } ;
struct proc {TYPE_1__* p_ucred; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int cr_ngroups; int* cr_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,int*,int) ; 

__attribute__((used)) static void
note_procstat_groups(void *arg, struct sbuf *sb, size_t *sizep)
{
	struct proc *p;
	size_t size;
	int structsize;

	p = (struct proc *)arg;
	size = sizeof(structsize) + p->p_ucred->cr_ngroups * sizeof(gid_t);
	if (sb != NULL) {
		KASSERT(*sizep == size, ("invalid size"));
		structsize = sizeof(gid_t);
		sbuf_bcat(sb, &structsize, sizeof(structsize));
		sbuf_bcat(sb, p->p_ucred->cr_groups, p->p_ucred->cr_ngroups *
		    sizeof(gid_t));
	}
	*sizep = size;
}