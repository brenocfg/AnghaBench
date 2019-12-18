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
struct mbuf {int m_type; scalar_t__ m_size; struct mbuf* m_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  fragments; } ;

/* Variables and functions */
 TYPE_1__* MemMap ; 

void
m_settype(struct mbuf *bp, int type)
{
  for (; bp; bp = bp->m_next)
    if (type != bp->m_type) {
      MemMap[bp->m_type].fragments--;
      MemMap[bp->m_type].octets -= bp->m_size;
      bp->m_type = type;
      MemMap[type].fragments++;
      MemMap[type].octets += bp->m_size;
    }
}