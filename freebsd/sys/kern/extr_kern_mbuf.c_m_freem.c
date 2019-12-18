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

/* Variables and functions */
 int /*<<< orphan*/  MBUF_PROBE1 (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  m__freem ; 
 struct mbuf* m_free (struct mbuf*) ; 

void
m_freem(struct mbuf *mb)
{

	MBUF_PROBE1(m__freem, mb);
	while (mb != NULL)
		mb = m_free(mb);
}