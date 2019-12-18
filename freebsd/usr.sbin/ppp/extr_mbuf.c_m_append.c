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
struct mbuf {size_t m_size; size_t m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 void* m_prepend (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

struct mbuf *
m_append(struct mbuf *bp, const void *v, size_t sz)
{
  struct mbuf *m = bp;

  if (m) {
    while (m->m_next)
      m = m->m_next;
    if (m->m_size - m->m_len >= sz) {
      if (v)
        memcpy((char *)(m + 1) + m->m_len, v, sz);
      m->m_len += sz;
    } else
      m->m_next = m_prepend(NULL, v, sz, 0);
  } else
    bp = m_prepend(NULL, v, sz, 0);

  return bp;
}