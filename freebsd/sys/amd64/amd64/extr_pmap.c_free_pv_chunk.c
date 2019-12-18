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
struct pv_chunks_list {int /*<<< orphan*/  pvc_lock; int /*<<< orphan*/  pvc_list; } ;
struct pv_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pv_chunk_dequeued (struct pv_chunk*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc_lru ; 
 size_t pc_to_domain (struct pv_chunk*) ; 
 struct pv_chunks_list* pv_chunks ; 

__attribute__((used)) static void
free_pv_chunk(struct pv_chunk *pc)
{
	struct pv_chunks_list *pvc;

	pvc = &pv_chunks[pc_to_domain(pc)];
	mtx_lock(&pvc->pvc_lock);
	TAILQ_REMOVE(&pvc->pvc_list, pc, pc_lru);
	mtx_unlock(&pvc->pvc_lock);
	free_pv_chunk_dequeued(pc);
}