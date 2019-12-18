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
struct umutex32 {uintptr_t m_rb_lnk; } ;
struct umutex {uintptr_t m_rb_lnk; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;
typedef  int /*<<< orphan*/  m32 ;

/* Variables and functions */
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct umutex32*,struct umutex*,int) ; 

__attribute__((used)) static void
umtx_read_rb_list(struct thread *td, struct umutex *m, uintptr_t *rb_list)
{
#ifdef COMPAT_FREEBSD32
	struct umutex32 m32;

	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		memcpy(&m32, m, sizeof(m32));
		*rb_list = m32.m_rb_lnk;
	} else
#endif
		*rb_list = m->m_rb_lnk;
}