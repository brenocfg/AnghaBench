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
struct TYPE_2__ {int /*<<< orphan*/  ext_pgs; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_EXT_PGS_ASSERT (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int sglist_count_ext_pgs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_offset_t ; 

int
sglist_count_mb_ext_pgs(struct mbuf *m)
{

	MBUF_EXT_PGS_ASSERT(m);
	return (sglist_count_ext_pgs(m->m_ext.ext_pgs, mtod(m, vm_offset_t),
	    m->m_len));
}