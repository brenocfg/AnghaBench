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
typedef  scalar_t__ uint32_t ;
struct test_transaction {int depth; int length; scalar_t__* buf; struct ioat_test* test; } ;
struct ioat_test {scalar_t__ transactions; int chain_depth; int /*<<< orphan*/  free_q; int /*<<< orphan*/ * status; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t IOAT_TEST_NO_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct test_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  ioat_test_log (int /*<<< orphan*/ ,char*) ; 
 struct test_transaction* ioat_test_transaction_create (struct ioat_test*,int) ; 

__attribute__((used)) static int
ioat_test_prealloc_memory(struct ioat_test *test, int index)
{
	uint32_t i, j, k;
	struct test_transaction *tx;

	for (i = 0; i < test->transactions; i++) {
		tx = ioat_test_transaction_create(test, test->chain_depth * 2);
		if (tx == NULL) {
			ioat_test_log(0, "tx == NULL - memory exhausted\n");
			test->status[IOAT_TEST_NO_MEMORY]++;
			return (ENOMEM);
		}

		TAILQ_INSERT_HEAD(&test->free_q, tx, entry);

		tx->test = test;
		tx->depth = test->chain_depth;

		/* fill in source buffers */
		for (j = 0; j < (tx->length / sizeof(uint32_t)); j++) {
			uint32_t val = j + (index << 28);

			for (k = 0; k < test->chain_depth; k++) {
				((uint32_t *)tx->buf[2*k])[j] = ~val;
				((uint32_t *)tx->buf[2*k+1])[j] = val;
			}
		}
	}
	return (0);
}