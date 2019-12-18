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
struct mbuf {int m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_WRITEBACK (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_fpa_free (int,int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int cvm_oct_mem_fill_fpa(int pool, int size, int elements)
{
	int freed = elements;
	while (freed) {
		KASSERT(size <= MCLBYTES - 128, ("mbuf clusters are too small"));

		struct mbuf *m = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
		if (__predict_false(m == NULL)) {
			printf("Failed to allocate mbuf for hardware pool %d\n", pool);
			break;
		}

		m->m_data += 128 - (((uintptr_t)m->m_data) & 0x7f);
		*(struct mbuf **)(m->m_data - sizeof(void *)) = m;
		cvmx_fpa_free(m->m_data, pool, DONT_WRITEBACK(size/128));
		freed--;
	}
	return (elements - freed);
}