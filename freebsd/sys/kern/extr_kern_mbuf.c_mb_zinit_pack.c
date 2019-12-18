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
struct TYPE_2__ {int /*<<< orphan*/ * ext_buf; int /*<<< orphan*/  ext_type; } ;
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT_PACKET ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  trash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uma_zalloc_arg (int /*<<< orphan*/ ,struct mbuf*,int) ; 
 int /*<<< orphan*/  zone_clust ; 

__attribute__((used)) static int
mb_zinit_pack(void *mem, int size, int how)
{
	struct mbuf *m;

	m = (struct mbuf *)mem;		/* m is virgin. */
	if (uma_zalloc_arg(zone_clust, m, how) == NULL ||
	    m->m_ext.ext_buf == NULL)
		return (ENOMEM);
	m->m_ext.ext_type = EXT_PACKET;	/* Override. */
#ifdef INVARIANTS
	trash_init(m->m_ext.ext_buf, MCLBYTES, how);
#endif
	return (0);
}