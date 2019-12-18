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
struct sockbuf {struct mbuf* sb_mbtail; } ;
struct mbuf {struct mbuf* m_next; } ;
struct TYPE_2__ {struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBLASTMBUFCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLINKRECORD (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_clrprotoflags (struct mbuf*) ; 
 TYPE_1__* m_last (struct mbuf*) ; 
 int /*<<< orphan*/  sballoc (struct sockbuf*,struct mbuf*) ; 

void
sbappendcontrol_locked(struct sockbuf *sb, struct mbuf *m0,
    struct mbuf *control)
{
	struct mbuf *m, *mlast;

	m_clrprotoflags(m0);
	m_last(control)->m_next = m0;

	SBLASTRECORDCHK(sb);

	for (m = control; m->m_next; m = m->m_next)
		sballoc(sb, m);
	sballoc(sb, m);
	mlast = m;
	SBLINKRECORD(sb, control);

	sb->sb_mbtail = mlast;
	SBLASTMBUFCHK(sb);

	SBLASTRECORDCHK(sb);
}