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
typedef  int /*<<< orphan*/  td_name ;
struct thread {int /*<<< orphan*/ * td_name; } ;
struct proc {int /*<<< orphan*/ * p_comm; } ;
struct kthr {int pid; scalar_t__ kaddr; scalar_t__ paddr; } ;
typedef  int /*<<< orphan*/  comm ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCOMLEN ; 
 struct kthr* kgdb_thr_lookup_tid (int) ; 
 int /*<<< orphan*/  kvm ; 
 int kvm_read (int /*<<< orphan*/ ,uintptr_t,char**,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

char *
kgdb_thr_extra_thread_info(int tid)
{
	char comm[MAXCOMLEN + 1];
	char td_name[MAXCOMLEN + 1];
	struct kthr *kt;
	struct proc *p;
	struct thread *t;
	static char buf[64];

	kt = kgdb_thr_lookup_tid(tid);
	if (kt == NULL)
		return (NULL);	
	snprintf(buf, sizeof(buf), "PID=%d", kt->pid);
	p = (struct proc *)kt->paddr;
	if (kvm_read(kvm, (uintptr_t)&p->p_comm[0], &comm, sizeof(comm)) !=
	    sizeof(comm))
		return (buf);
	strlcat(buf, ": ", sizeof(buf));
	strlcat(buf, comm, sizeof(buf));
	t = (struct thread *)kt->kaddr;
	if (kvm_read(kvm, (uintptr_t)&t->td_name[0], &td_name,
	    sizeof(td_name)) == sizeof(td_name) &&
	    strcmp(comm, td_name) != 0) {
		strlcat(buf, "/", sizeof(buf));
		strlcat(buf, td_name, sizeof(buf));
	}
	return (buf);
}