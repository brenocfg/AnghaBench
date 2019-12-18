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
struct proc {int p_numthreads; } ;
struct kinfo_proc32 {int dummy; } ;
struct kinfo_proc {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int KERN_PROC_MASK32 ; 
 int KERN_PROC_NOTHREADS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 

__attribute__((used)) static ssize_t
kern_proc_out_size(struct proc *p, int flags)
{
	ssize_t size = 0;

	PROC_LOCK_ASSERT(p, MA_OWNED);

	if ((flags & KERN_PROC_NOTHREADS) != 0) {
#ifdef COMPAT_FREEBSD32
		if ((flags & KERN_PROC_MASK32) != 0) {
			size += sizeof(struct kinfo_proc32);
		} else
#endif
			size += sizeof(struct kinfo_proc);
	} else {
#ifdef COMPAT_FREEBSD32
		if ((flags & KERN_PROC_MASK32) != 0)
			size += sizeof(struct kinfo_proc32) * p->p_numthreads;
		else
#endif
			size += sizeof(struct kinfo_proc) * p->p_numthreads;
	}
	PROC_UNLOCK(p);
	return (size);
}