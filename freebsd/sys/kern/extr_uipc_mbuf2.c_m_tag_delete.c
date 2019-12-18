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
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  m_tag_free (struct m_tag*) ; 
 int /*<<< orphan*/  m_tag_unlink (struct mbuf*,struct m_tag*) ; 

void
m_tag_delete(struct mbuf *m, struct m_tag *t)
{

	KASSERT(m && t, ("m_tag_delete: null argument, m %p t %p", m, t));
	m_tag_unlink(m, t);
	m_tag_free(t);
}