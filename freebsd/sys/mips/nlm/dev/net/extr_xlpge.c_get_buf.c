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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {scalar_t__ m_data; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int NAE_CACHELINE_SIZE ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vtophys (scalar_t__) ; 

__attribute__((used)) static void *
get_buf(void)
{
	struct mbuf     *m_new;
	uint64_t        *md;
#ifdef INVARIANTS
	vm_paddr_t      temp1, temp2;
#endif

	if ((m_new = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR)) == NULL)
		return (NULL);
	m_new->m_len = m_new->m_pkthdr.len = MCLBYTES;
	KASSERT(((uintptr_t)m_new->m_data & (NAE_CACHELINE_SIZE - 1)) == 0,
	    ("m_new->m_data is not cacheline aligned"));
	md = (uint64_t *)m_new->m_data;
	md[0] = (intptr_t)m_new;        /* Back Ptr */
	md[1] = 0xf00bad;
	m_adj(m_new, NAE_CACHELINE_SIZE);

#ifdef INVARIANTS
	temp1 = vtophys((vm_offset_t) m_new->m_data);
	temp2 = vtophys((vm_offset_t) m_new->m_data + 1536);
	KASSERT((temp1 + 1536) == temp2,
	    ("Alloced buffer is not contiguous"));
#endif
	return ((void *)m_new->m_data);
}