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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ uint64_t ;
struct octeon_device {int dummy; } ;
struct lio_sg_entry {int dummy; } ;
struct lio_gather {int /*<<< orphan*/  node; scalar_t__ sg_dma_ptr; struct lio_sg_entry* sg; } ;
struct lio {int glist_entry_size; int tx_qsize; int /*<<< orphan*/ * ghead; scalar_t__* glists_dma_base; int /*<<< orphan*/ ** glists_virt_base; int /*<<< orphan*/ * glist_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_MAX_SG ; 
 int LIO_SG_ENTRY_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int ROUNDUP4 (int /*<<< orphan*/ ) ; 
 int ROUNDUP8 (int) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_delete_glists (struct octeon_device*,struct lio*) ; 
 int /*<<< orphan*/ * lio_dma_alloc (int,int /*<<< orphan*/ *) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_setup_glists(struct octeon_device *oct, struct lio *lio, int num_iqs)
{
	struct lio_gather	*g;
	int	i, j;

	lio->glist_lock = malloc(num_iqs * sizeof(*lio->glist_lock), M_DEVBUF,
				 M_NOWAIT | M_ZERO);
	if (lio->glist_lock == NULL)
		return (1);

	lio->ghead = malloc(num_iqs * sizeof(*lio->ghead), M_DEVBUF,
			    M_NOWAIT | M_ZERO);
	if (lio->ghead == NULL) {
		free((void *)lio->glist_lock, M_DEVBUF);
		lio->glist_lock = NULL;
		return (1);
	}

	lio->glist_entry_size = ROUNDUP8((ROUNDUP4(LIO_MAX_SG) >> 2) *
					 LIO_SG_ENTRY_SIZE);
	/*
	 * allocate memory to store virtual and dma base address of
	 * per glist consistent memory
	 */
	lio->glists_virt_base = malloc(num_iqs * sizeof(void *), M_DEVBUF,
				       M_NOWAIT | M_ZERO);
	lio->glists_dma_base = malloc(num_iqs * sizeof(vm_paddr_t), M_DEVBUF,
				      M_NOWAIT | M_ZERO);
	if ((lio->glists_virt_base == NULL) || (lio->glists_dma_base == NULL)) {
		lio_delete_glists(oct, lio);
		return (1);
	}

	for (i = 0; i < num_iqs; i++) {
		mtx_init(&lio->glist_lock[i], "glist_lock", NULL, MTX_DEF);

		STAILQ_INIT(&lio->ghead[i]);

		lio->glists_virt_base[i] =
		    lio_dma_alloc(lio->glist_entry_size * lio->tx_qsize,
				  (vm_paddr_t *)&lio->glists_dma_base[i]);
		if (lio->glists_virt_base[i] == NULL) {
			lio_delete_glists(oct, lio);
			return (1);
		}

		for (j = 0; j < lio->tx_qsize; j++) {
			g = malloc(sizeof(*g), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (g == NULL)
				break;

			g->sg = (struct lio_sg_entry *)(uintptr_t)
			    ((uint64_t)(uintptr_t)lio->glists_virt_base[i] +
			     (j * lio->glist_entry_size));
			g->sg_dma_ptr = (uint64_t)lio->glists_dma_base[i] +
				(j * lio->glist_entry_size);
			STAILQ_INSERT_TAIL(&lio->ghead[i], &g->node, entries);
		}

		if (j != lio->tx_qsize) {
			lio_delete_glists(oct, lio);
			return (1);
		}
	}

	return (0);
}