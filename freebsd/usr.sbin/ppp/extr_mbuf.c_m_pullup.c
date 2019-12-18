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
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int m_offset; int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_type; int /*<<< orphan*/ * m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_free (struct mbuf*) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_length (struct mbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct mbuf *
m_pullup(struct mbuf *bp)
{
  /* Put it all in one contigous (aligned) mbuf */

  if (bp != NULL) {
    if (bp->m_next != NULL) {
      struct mbuf *nbp;
      u_char *cp;

      nbp = m_get(m_length(bp), bp->m_type);

      for (cp = MBUF_CTOP(nbp); bp; bp = m_free(bp)) {
        memcpy(cp, MBUF_CTOP(bp), bp->m_len);
        cp += bp->m_len;
      }
      bp = nbp;
    }
#ifndef __i386__	/* Do any other archs not care about alignment ? */
    else if ((bp->m_offset & (sizeof(long) - 1)) != 0) {
      bcopy(MBUF_CTOP(bp), bp + 1, bp->m_len);
      bp->m_offset = 0;
    }
#endif
  }

  return bp;
}