#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbuf {size_t m_type; scalar_t__ m_size; struct mbuf* m_next; } ;
struct TYPE_4__ {int count; struct mbucket* next; } ;
struct TYPE_5__ {TYPE_1__ f; } ;
struct mbucket {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  fragments; } ;

/* Variables and functions */
 struct mbucket** M_BUCKET (scalar_t__) ; 
 TYPE_3__* MemMap ; 
 int /*<<< orphan*/  mbuf_Frees ; 

struct mbuf *
m_free(struct mbuf *bp)
{
  struct mbucket **mb, *f;
  struct mbuf *nbp;

  if ((f = (struct mbucket *)bp) != NULL) {
    MemMap[bp->m_type].fragments--;
    MemMap[bp->m_type].octets -= bp->m_size;

    nbp = bp->m_next;
    mb = M_BUCKET(bp->m_size);
    f->u.f.next = *mb;
    f->u.f.count = 1;
    *mb = f;

    mbuf_Frees++;
    bp = nbp;
  }

  return bp;
}