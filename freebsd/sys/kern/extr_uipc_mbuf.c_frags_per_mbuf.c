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
struct mbuf_ext_pgs {scalar_t__ hdr_len; scalar_t__ trail_len; scalar_t__ npgs; } ;
struct TYPE_2__ {struct mbuf_ext_pgs* ext_pgs; } ;
struct mbuf {int m_flags; TYPE_1__ m_ext; } ;

/* Variables and functions */
 int M_NOMAP ; 

__attribute__((used)) static int
frags_per_mbuf(struct mbuf *m)
{
	struct mbuf_ext_pgs *ext_pgs;
	int frags;

	if ((m->m_flags & M_NOMAP) == 0)
		return (1);

	/*
	 * The header and trailer are counted as a single fragment
	 * each when present.
	 *
	 * XXX: This overestimates the number of fragments by assuming
	 * all the backing physical pages are disjoint.
	 */
	ext_pgs = m->m_ext.ext_pgs;
	frags = 0;
	if (ext_pgs->hdr_len != 0)
		frags++;
	frags += ext_pgs->npgs;
	if (ext_pgs->trail_len != 0)
		frags++;

	return (frags);
}