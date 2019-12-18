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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct test_transaction {int depth; int /*<<< orphan*/  length; scalar_t__* crc; scalar_t__* buf; } ;
struct ioat_test {scalar_t__ testkind; int /*<<< orphan*/  free_q; int /*<<< orphan*/  pend_q; int /*<<< orphan*/ * status; int /*<<< orphan*/  raw_target; scalar_t__ raw_write; } ;
struct bus_dmadesc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmaengine_t ;
typedef  int /*<<< orphan*/  (* bus_dmaengine_callback_t ) (struct test_transaction*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int DMA_CRC_STORE ; 
 int DMA_INT_EN ; 
 scalar_t__ IOAT_TEST_DMA ; 
 scalar_t__ IOAT_TEST_DMA_8K ; 
 scalar_t__ IOAT_TEST_DMA_8K_PB ; 
 scalar_t__ IOAT_TEST_DMA_CRC ; 
 scalar_t__ IOAT_TEST_DMA_CRC_COPY ; 
 scalar_t__ IOAT_TEST_FILL ; 
 scalar_t__ IOAT_TEST_MEMCPY ; 
 size_t IOAT_TEST_NO_DMA_ENGINE ; 
 scalar_t__ IOAT_TEST_RAW_DMA ; 
 int /*<<< orphan*/  IT_LOCK () ; 
 int /*<<< orphan*/  IT_UNLOCK () ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct test_transaction* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct test_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct test_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  ioat_acquire (int /*<<< orphan*/ ) ; 
 struct bus_dmadesc* ioat_blockfill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct test_transaction*,int /*<<< orphan*/ ),struct test_transaction*,int) ; 
 struct bus_dmadesc* ioat_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct test_transaction*,int /*<<< orphan*/ ),struct test_transaction*,int) ; 
 struct bus_dmadesc* ioat_copy_8k_aligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct test_transaction*,int /*<<< orphan*/ ),struct test_transaction*,int) ; 
 struct bus_dmadesc* ioat_copy_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct test_transaction*,int /*<<< orphan*/ ),struct test_transaction*,int) ; 
 struct bus_dmadesc* ioat_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct test_transaction*,int /*<<< orphan*/ ),struct test_transaction*,int) ; 
 int /*<<< orphan*/  ioat_dma_test_callback (struct test_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_test_lk ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (scalar_t__) ; 

__attribute__((used)) static void
ioat_test_submit_1_tx(struct ioat_test *test, bus_dmaengine_t dma)
{
	struct test_transaction *tx;
	struct bus_dmadesc *desc;
	bus_dmaengine_callback_t cb;
	bus_addr_t src, dest;
	uint64_t fillpattern;
	uint32_t i, flags;

	desc = NULL;

	IT_LOCK();
	while (TAILQ_EMPTY(&test->free_q))
		msleep(&test->free_q, &ioat_test_lk, 0, "test_submit", 0);

	tx = TAILQ_FIRST(&test->free_q);
	TAILQ_REMOVE(&test->free_q, tx, entry);
	TAILQ_INSERT_HEAD(&test->pend_q, tx, entry);
	IT_UNLOCK();

	if (test->testkind != IOAT_TEST_MEMCPY)
		ioat_acquire(dma);
	for (i = 0; i < tx->depth; i++) {
		if (test->testkind == IOAT_TEST_MEMCPY) {
			memcpy(tx->buf[2 * i + 1], tx->buf[2 * i], tx->length);
			if (i == tx->depth - 1)
				ioat_dma_test_callback(tx, 0);
			continue;
		}

		src = vtophys((vm_offset_t)tx->buf[2*i]);
		dest = vtophys((vm_offset_t)tx->buf[2*i+1]);

		if (test->testkind == IOAT_TEST_RAW_DMA) {
			if (test->raw_write)
				dest = test->raw_target;
			else
				src = test->raw_target;
		}

		if (i == tx->depth - 1) {
			cb = ioat_dma_test_callback;
			flags = DMA_INT_EN;
		} else {
			cb = NULL;
			flags = 0;
		}

		if (test->testkind == IOAT_TEST_DMA ||
		    test->testkind == IOAT_TEST_RAW_DMA)
			desc = ioat_copy(dma, dest, src, tx->length, cb, tx,
			    flags);
		else if (test->testkind == IOAT_TEST_FILL) {
			fillpattern = *(uint64_t *)tx->buf[2*i];
			desc = ioat_blockfill(dma, dest, fillpattern,
			    tx->length, cb, tx, flags);
		} else if (test->testkind == IOAT_TEST_DMA_8K) {
			bus_addr_t src2, dst2;

			src2 = vtophys((vm_offset_t)tx->buf[2*i] + PAGE_SIZE);
			dst2 = vtophys((vm_offset_t)tx->buf[2*i+1] + PAGE_SIZE);

			desc = ioat_copy_8k_aligned(dma, dest, dst2, src, src2,
			    cb, tx, flags);
		} else if (test->testkind == IOAT_TEST_DMA_8K_PB) {
			bus_addr_t src2, dst2;

			src2 = vtophys((vm_offset_t)tx->buf[2*i+1] + PAGE_SIZE);
			dst2 = vtophys((vm_offset_t)tx->buf[2*i] + PAGE_SIZE);

			desc = ioat_copy_8k_aligned(dma, dest, dst2, src, src2,
			    cb, tx, flags);
		} else if (test->testkind == IOAT_TEST_DMA_CRC) {
			bus_addr_t crc;

			tx->crc[i] = 0;
			crc = vtophys((vm_offset_t)&tx->crc[i]);
			desc = ioat_crc(dma, src, tx->length,
			    NULL, crc, cb, tx, flags | DMA_CRC_STORE);
		} else if (test->testkind == IOAT_TEST_DMA_CRC_COPY) {
			bus_addr_t crc;

			tx->crc[i] = 0;
			crc = vtophys((vm_offset_t)&tx->crc[i]);
			desc = ioat_copy_crc(dma, dest, src, tx->length,
			    NULL, crc, cb, tx, flags | DMA_CRC_STORE);
		}
		if (desc == NULL)
			break;
	}
	if (test->testkind == IOAT_TEST_MEMCPY)
		return;
	ioat_release(dma);

	/*
	 * We couldn't issue an IO -- either the device is being detached or
	 * the HW reset.  Essentially spin until the device comes back up or
	 * our timer expires.
	 */
	if (desc == NULL && tx->depth > 0) {
		atomic_add_32(&test->status[IOAT_TEST_NO_DMA_ENGINE], tx->depth);
		IT_LOCK();
		TAILQ_REMOVE(&test->pend_q, tx, entry);
		TAILQ_INSERT_HEAD(&test->free_q, tx, entry);
		IT_UNLOCK();
	}
}