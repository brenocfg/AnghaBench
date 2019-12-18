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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  head; int /*<<< orphan*/  alloc_buf_count; int /*<<< orphan*/  lock; } ;
struct octeon_device {TYPE_1__ sc_buf_pool; } ;
struct lio_soft_command {int /*<<< orphan*/  node; int /*<<< orphan*/  size; scalar_t__ dma_addr; } ;

/* Variables and functions */
 int LIO_MAX_SOFT_COMMAND_BUFFERS ; 
 int /*<<< orphan*/  LIO_SOFT_COMMAND_BUFFER_SIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 scalar_t__ lio_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_free_sc_buffer_pool (struct octeon_device*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
lio_setup_sc_buffer_pool(struct octeon_device *oct)
{
	struct lio_soft_command	*sc;
	uint64_t		dma_addr;
	int			i;

	STAILQ_INIT(&oct->sc_buf_pool.head);
	mtx_init(&oct->sc_buf_pool.lock, "sc_pool_lock", NULL, MTX_DEF);
	atomic_store_rel_int(&oct->sc_buf_pool.alloc_buf_count, 0);

	for (i = 0; i < LIO_MAX_SOFT_COMMAND_BUFFERS; i++) {
		sc = (struct lio_soft_command *)
			lio_dma_alloc(LIO_SOFT_COMMAND_BUFFER_SIZE, (vm_paddr_t *)&dma_addr);
		if (sc == NULL) {
			lio_free_sc_buffer_pool(oct);
			return (1);
		}

		sc->dma_addr = dma_addr;
		sc->size = LIO_SOFT_COMMAND_BUFFER_SIZE;

		STAILQ_INSERT_TAIL(&oct->sc_buf_pool.head, &sc->node, entries);
	}

	return (0);
}