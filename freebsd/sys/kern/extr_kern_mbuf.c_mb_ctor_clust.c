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
struct TYPE_2__ {char* ext_buf; int ext_size; int ext_count; int /*<<< orphan*/  ext_flags; int /*<<< orphan*/  ext_type; int /*<<< orphan*/ * ext_arg2; int /*<<< orphan*/ * ext_arg1; int /*<<< orphan*/ * ext_free; } ;
struct mbuf {char* m_data; TYPE_1__ m_ext; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_FLAG_EMBREF ; 
 int /*<<< orphan*/  M_EXT ; 
 int /*<<< orphan*/  m_gettype (int) ; 
 int /*<<< orphan*/  trash_ctor (void*,int,void*,int) ; 

__attribute__((used)) static int
mb_ctor_clust(void *mem, int size, void *arg, int how)
{
	struct mbuf *m;

#ifdef INVARIANTS
	trash_ctor(mem, size, arg, how);
#endif
	m = (struct mbuf *)arg;
	if (m != NULL) {
		m->m_ext.ext_buf = (char *)mem;
		m->m_data = m->m_ext.ext_buf;
		m->m_flags |= M_EXT;
		m->m_ext.ext_free = NULL;
		m->m_ext.ext_arg1 = NULL;
		m->m_ext.ext_arg2 = NULL;
		m->m_ext.ext_size = size;
		m->m_ext.ext_type = m_gettype(size);
		m->m_ext.ext_flags = EXT_FLAG_EMBREF;
		m->m_ext.ext_count = 1;
	}

	return (0);
}