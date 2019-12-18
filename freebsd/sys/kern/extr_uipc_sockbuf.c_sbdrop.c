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
struct sockbuf {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* sbcut_internal (struct sockbuf*,int) ; 

void
sbdrop(struct sockbuf *sb, int len)
{
	struct mbuf *mfree;

	SOCKBUF_LOCK(sb);
	mfree = sbcut_internal(sb, len);
	SOCKBUF_UNLOCK(sb);

	m_freem(mfree);
}