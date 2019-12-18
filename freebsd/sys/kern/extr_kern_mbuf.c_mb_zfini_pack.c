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
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  trash_dtor (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trash_fini (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zone_clust ; 

__attribute__((used)) static void
mb_zfini_pack(void *mem, int size)
{
	struct mbuf *m;

	m = (struct mbuf *)mem;
#ifdef INVARIANTS
	trash_fini(m->m_ext.ext_buf, MCLBYTES);
#endif
	uma_zfree_arg(zone_clust, m->m_ext.ext_buf, NULL);
#ifdef INVARIANTS
	trash_dtor(mem, size, NULL);
#endif
}