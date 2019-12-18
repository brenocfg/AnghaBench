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
typedef  int u_long ;
struct thread {int dummy; } ;
struct socket {TYPE_1__* so_cred; } ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_lowat; int /*<<< orphan*/  sb_mbmax; } ;
typedef  int /*<<< orphan*/  rlim_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uidinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_SBSIZE ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  chgsbsize (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int sb_efficiency ; 
 int /*<<< orphan*/  sb_max ; 
 int sb_max_adj ; 

int
sbreserve_locked(struct sockbuf *sb, u_long cc, struct socket *so,
    struct thread *td)
{
	rlim_t sbsize_limit;

	SOCKBUF_LOCK_ASSERT(sb);

	/*
	 * When a thread is passed, we take into account the thread's socket
	 * buffer size limit.  The caller will generally pass curthread, but
	 * in the TCP input path, NULL will be passed to indicate that no
	 * appropriate thread resource limits are available.  In that case,
	 * we don't apply a process limit.
	 */
	if (cc > sb_max_adj)
		return (0);
	if (td != NULL) {
		sbsize_limit = lim_cur(td, RLIMIT_SBSIZE);
	} else
		sbsize_limit = RLIM_INFINITY;
	if (!chgsbsize(so->so_cred->cr_uidinfo, &sb->sb_hiwat, cc,
	    sbsize_limit))
		return (0);
	sb->sb_mbmax = min(cc * sb_efficiency, sb_max);
	if (sb->sb_lowat > sb->sb_hiwat)
		sb->sb_lowat = sb->sb_hiwat;
	return (1);
}