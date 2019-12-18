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
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;

/* Variables and functions */

size_t
m_length(struct mbuf *bp)
{
  size_t len;

  for (len = 0; bp; bp = bp->m_next)
    len += bp->m_len;
  return len;
}