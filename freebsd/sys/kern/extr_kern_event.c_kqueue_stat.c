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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

__attribute__((used)) static int
kqueue_stat(struct file *fp, struct stat *st, struct ucred *active_cred,
	struct thread *td)
{

	bzero((void *)st, sizeof *st);
	/*
	 * We no longer return kq_count because the unlocked value is useless.
	 * If you spent all this time getting the count, why not spend your
	 * syscall better by calling kevent?
	 *
	 * XXX - This is needed for libc_r.
	 */
	st->st_mode = S_IFIFO;
	return (0);
}