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
struct m_pool {int /*<<< orphan*/  nump; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 struct m_pool* ___cre_dma_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ___del_dma_pool (struct m_pool*) ; 
 struct m_pool* ___get_dma_pool (int /*<<< orphan*/ ) ; 
 void* __sym_calloc (struct m_pool*,int,char*) ; 

__attribute__((used)) static void *__sym_calloc_dma(bus_dma_tag_t dev_dmat, int size, char *name)
{
	struct m_pool *mp;
	void *m = NULL;

	/* Lock */
	mp = ___get_dma_pool(dev_dmat);
	if (!mp)
		mp = ___cre_dma_pool(dev_dmat);
	if (mp)
		m = __sym_calloc(mp, size, name);
#ifdef	MEMO_FREE_UNUSED
	if (mp && !mp->nump)
		___del_dma_pool(mp);
#endif
	/* Unlock */

	return m;
}