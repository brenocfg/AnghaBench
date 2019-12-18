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
struct sglist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_pgs; } ;
struct mbuf {int /*<<< orphan*/  m_len; TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_EXT_PGS_ASSERT (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int sglist_append_ext_pgs (struct sglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_offset_t ; 

int
sglist_append_mb_ext_pgs(struct sglist *sg, struct mbuf *m)
{

	/* for now, all unmapped mbufs are assumed to be EXT_PGS */
	MBUF_EXT_PGS_ASSERT(m);
	return (sglist_append_ext_pgs(sg, m->m_ext.ext_pgs,
	    mtod(m, vm_offset_t), m->m_len));
}