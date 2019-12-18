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
struct sockbuf {struct mbuf* sb_mb; struct mbuf* sb_lastrecord; int /*<<< orphan*/ * sb_mbtail; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 

__attribute__((used)) static __inline void
sockbuf_pushsync(struct sockbuf *sb, struct mbuf *nextrecord)
{

	SOCKBUF_LOCK_ASSERT(sb);
	/*
	 * First, update for the new value of nextrecord.  If necessary, make
	 * it the first record.
	 */
	if (sb->sb_mb != NULL)
		sb->sb_mb->m_nextpkt = nextrecord;
	else
		sb->sb_mb = nextrecord;

	/*
	 * Now update any dependent socket buffer fields to reflect the new
	 * state.  This is an expanded inline of SB_EMPTY_FIXUP(), with the
	 * addition of a second clause that takes care of the case where
	 * sb_mb has been updated, but remains the last record.
	 */
	if (sb->sb_mb == NULL) {
		sb->sb_mbtail = NULL;
		sb->sb_lastrecord = NULL;
	} else if (sb->sb_mb->m_nextpkt == NULL)
		sb->sb_lastrecord = sb->sb_mb;
}