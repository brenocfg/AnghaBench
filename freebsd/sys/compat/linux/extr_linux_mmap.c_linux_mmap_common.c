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
struct vmspace {scalar_t__ vm_maxsaddr; } ;
struct thread {int /*<<< orphan*/ * td_retval; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; struct vmspace* p_vmspace; } ;
struct file {scalar_t__ f_type; int f_flag; } ;
typedef  int off_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {scalar_t__ sv_usrstack; } ;

/* Variables and functions */
 scalar_t__ DTYPE_DEV ; 
 scalar_t__ DTYPE_VNODE ; 
 int EACCES ; 
 int EINVAL ; 
 int FREAD ; 
 size_t GUARD_SIZE ; 
 int /*<<< orphan*/  LINUX_CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINUX_CTR6 (int /*<<< orphan*/ ,char*,uintptr_t,size_t,int,int,int,int) ; 
 int LINUX_MAP_ANON ; 
 int LINUX_MAP_FIXED ; 
 int LINUX_MAP_GROWSDOWN ; 
 int LINUX_MAP_PRIVATE ; 
 int LINUX_MAP_SHARED ; 
 int MAP_ANON ; 
 int MAP_EXCL ; 
 int MAP_FIXED ; 
 int MAP_NOSYNC ; 
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int MAP_STACK ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 size_t STACK_SIZE ; 
 int /*<<< orphan*/  cap_mmap_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int kern_mmap (struct thread*,uintptr_t,size_t,int,int,int,int) ; 
 int lim_cur_proc (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_fixup_prot (struct thread*,int*) ; 
 int /*<<< orphan*/  mmap2 ; 

int
linux_mmap_common(struct thread *td, uintptr_t addr, size_t len, int prot,
    int flags, int fd, off_t pos)
{
	struct proc *p = td->td_proc;
	struct vmspace *vms = td->td_proc->p_vmspace;
	int bsd_flags, error;
	struct file *fp;

	LINUX_CTR6(mmap2, "0x%lx, %ld, %ld, 0x%08lx, %ld, 0x%lx",
	    addr, len, prot, flags, fd, pos);

	error = 0;
	bsd_flags = 0;
	fp = NULL;

	/*
	 * Linux mmap(2):
	 * You must specify exactly one of MAP_SHARED and MAP_PRIVATE
	 */
	if (!((flags & LINUX_MAP_SHARED) ^ (flags & LINUX_MAP_PRIVATE)))
		return (EINVAL);

	if (flags & LINUX_MAP_SHARED)
		bsd_flags |= MAP_SHARED;
	if (flags & LINUX_MAP_PRIVATE)
		bsd_flags |= MAP_PRIVATE;
	if (flags & LINUX_MAP_FIXED)
		bsd_flags |= MAP_FIXED;
	if (flags & LINUX_MAP_ANON) {
		/* Enforce pos to be on page boundary, then ignore. */
		if ((pos & PAGE_MASK) != 0)
			return (EINVAL);
		pos = 0;
		bsd_flags |= MAP_ANON;
	} else
		bsd_flags |= MAP_NOSYNC;
	if (flags & LINUX_MAP_GROWSDOWN)
		bsd_flags |= MAP_STACK;

	/*
	 * PROT_READ, PROT_WRITE, or PROT_EXEC implies PROT_READ and PROT_EXEC
	 * on Linux/i386 if the binary requires executable stack.
	 * We do this only for IA32 emulation as on native i386 this is does not
	 * make sense without PAE.
	 *
	 * XXX. Linux checks that the file system is not mounted with noexec.
	 */
#if defined(__amd64__)
	linux_fixup_prot(td, &prot);
#endif

	/* Linux does not check file descriptor when MAP_ANONYMOUS is set. */
	fd = (bsd_flags & MAP_ANON) ? -1 : fd;
	if (fd != -1) {
		/*
		 * Linux follows Solaris mmap(2) description:
		 * The file descriptor fildes is opened with
		 * read permission, regardless of the
		 * protection options specified.
		 */

		error = fget(td, fd, &cap_mmap_rights, &fp);
		if (error != 0)
			return (error);
		if (fp->f_type != DTYPE_VNODE && fp->f_type != DTYPE_DEV) {
			fdrop(fp, td);
			return (EINVAL);
		}

		/* Linux mmap() just fails for O_WRONLY files */
		if (!(fp->f_flag & FREAD)) {
			fdrop(fp, td);
			return (EACCES);
		}

		fdrop(fp, td);
	}

	if (flags & LINUX_MAP_GROWSDOWN) {
		/*
		 * The Linux MAP_GROWSDOWN option does not limit auto
		 * growth of the region.  Linux mmap with this option
		 * takes as addr the initial BOS, and as len, the initial
		 * region size.  It can then grow down from addr without
		 * limit.  However, Linux threads has an implicit internal
		 * limit to stack size of STACK_SIZE.  Its just not
		 * enforced explicitly in Linux.  But, here we impose
		 * a limit of (STACK_SIZE - GUARD_SIZE) on the stack
		 * region, since we can do this with our mmap.
		 *
		 * Our mmap with MAP_STACK takes addr as the maximum
		 * downsize limit on BOS, and as len the max size of
		 * the region.  It then maps the top SGROWSIZ bytes,
		 * and auto grows the region down, up to the limit
		 * in addr.
		 *
		 * If we don't use the MAP_STACK option, the effect
		 * of this code is to allocate a stack region of a
		 * fixed size of (STACK_SIZE - GUARD_SIZE).
		 */

		if ((caddr_t)addr + len > vms->vm_maxsaddr) {
			/*
			 * Some Linux apps will attempt to mmap
			 * thread stacks near the top of their
			 * address space.  If their TOS is greater
			 * than vm_maxsaddr, vm_map_growstack()
			 * will confuse the thread stack with the
			 * process stack and deliver a SEGV if they
			 * attempt to grow the thread stack past their
			 * current stacksize rlimit.  To avoid this,
			 * adjust vm_maxsaddr upwards to reflect
			 * the current stacksize rlimit rather
			 * than the maximum possible stacksize.
			 * It would be better to adjust the
			 * mmap'ed region, but some apps do not check
			 * mmap's return value.
			 */
			PROC_LOCK(p);
			vms->vm_maxsaddr = (char *)p->p_sysent->sv_usrstack -
			    lim_cur_proc(p, RLIMIT_STACK);
			PROC_UNLOCK(p);
		}

		/*
		 * This gives us our maximum stack size and a new BOS.
		 * If we're using VM_STACK, then mmap will just map
		 * the top SGROWSIZ bytes, and let the stack grow down
		 * to the limit at BOS.  If we're not using VM_STACK
		 * we map the full stack, since we don't have a way
		 * to autogrow it.
		 */
		if (len <= STACK_SIZE - GUARD_SIZE) {
			addr = addr - (STACK_SIZE - GUARD_SIZE - len);
			len = STACK_SIZE - GUARD_SIZE;
		}
	}

	/*
	 * FreeBSD is free to ignore the address hint if MAP_FIXED wasn't
	 * passed.  However, some Linux applications, like the ART runtime,
	 * depend on the hint.  If the MAP_FIXED wasn't passed, but the
	 * address is not zero, try with MAP_FIXED and MAP_EXCL first,
	 * and fall back to the normal behaviour if that fails.
	 */
	if (addr != 0 && (bsd_flags & MAP_FIXED) == 0 &&
	    (bsd_flags & MAP_EXCL) == 0) {
		error = kern_mmap(td, addr, len, prot,
		    bsd_flags | MAP_FIXED | MAP_EXCL, fd, pos);
		if (error == 0)
			goto out;
	}

	error = kern_mmap(td, addr, len, prot, bsd_flags, fd, pos);
out:
	LINUX_CTR2(mmap2, "return: %d (%p)", error, td->td_retval[0]);

	return (error);
}