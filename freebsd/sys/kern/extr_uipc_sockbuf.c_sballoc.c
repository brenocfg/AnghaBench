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
struct sockbuf {int sb_mcnt; int sb_ccnt; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_ctl; int /*<<< orphan*/  sb_acc; struct mbuf* sb_fnrdy; int /*<<< orphan*/  sb_ccc; } ;
struct TYPE_2__ {scalar_t__ ext_size; } ;
struct mbuf {int m_flags; scalar_t__ m_type; TYPE_1__ m_ext; scalar_t__ m_len; } ;

/* Variables and functions */
 scalar_t__ MSIZE ; 
 scalar_t__ MT_DATA ; 
 scalar_t__ MT_OOBDATA ; 
 int M_BLOCKED ; 
 int M_EXT ; 
 int M_NOTREADY ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 

void
sballoc(struct sockbuf *sb, struct mbuf *m)
{

	SOCKBUF_LOCK_ASSERT(sb);

	sb->sb_ccc += m->m_len;

	if (sb->sb_fnrdy == NULL) {
		if (m->m_flags & M_NOTREADY)
			sb->sb_fnrdy = m;
		else
			sb->sb_acc += m->m_len;
	} else
		m->m_flags |= M_BLOCKED;

	if (m->m_type != MT_DATA && m->m_type != MT_OOBDATA)
		sb->sb_ctl += m->m_len;

	sb->sb_mbcnt += MSIZE;
	sb->sb_mcnt += 1;

	if (m->m_flags & M_EXT) {
		sb->sb_mbcnt += m->m_ext.ext_size;
		sb->sb_ccnt += 1;
	}
}