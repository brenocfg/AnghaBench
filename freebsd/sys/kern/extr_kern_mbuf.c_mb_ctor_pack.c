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
struct TYPE_2__ {int /*<<< orphan*/  ext_buf; } ;
struct mbuf {int m_flags; TYPE_1__ m_ext; int /*<<< orphan*/  m_data; } ;
struct mb_args {int flags; short type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_EXT ; 
 int M_NOFREE ; 
 int m_init (struct mbuf*,int,short,int) ; 
 int /*<<< orphan*/  trash_ctor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int
mb_ctor_pack(void *mem, int size, void *arg, int how)
{
	struct mbuf *m;
	struct mb_args *args;
	int error, flags;
	short type;

	m = (struct mbuf *)mem;
	args = (struct mb_args *)arg;
	flags = args->flags;
	type = args->type;
	MPASS((flags & M_NOFREE) == 0);

#ifdef INVARIANTS
	trash_ctor(m->m_ext.ext_buf, MCLBYTES, arg, how);
#endif

	error = m_init(m, how, type, flags);

	/* m_ext is already initialized. */
	m->m_data = m->m_ext.ext_buf;
 	m->m_flags = (flags | M_EXT);

	return (error);
}