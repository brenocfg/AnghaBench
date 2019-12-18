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
struct test_transaction {int length; int /*<<< orphan*/ ** buf; } ;
struct ioat_test {int buffer_size; scalar_t__ testkind; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 scalar_t__ IOAT_TEST_DMA_8K ; 
 int /*<<< orphan*/  M_IOAT_TEST ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * contigmalloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_test_transaction_destroy (struct test_transaction*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct
test_transaction *ioat_test_transaction_create(struct ioat_test *test,
    unsigned num_buffers)
{
	struct test_transaction *tx;
	unsigned i;

	tx = malloc(sizeof(*tx), M_IOAT_TEST, M_NOWAIT | M_ZERO);
	if (tx == NULL)
		return (NULL);

	tx->length = test->buffer_size;

	for (i = 0; i < num_buffers; i++) {
		if (test->testkind == IOAT_TEST_DMA_8K)
			tx->buf[i] = malloc(test->buffer_size, M_IOAT_TEST,
			    M_NOWAIT);
		else
			tx->buf[i] = contigmalloc(test->buffer_size,
			    M_IOAT_TEST, M_NOWAIT, 0, BUS_SPACE_MAXADDR,
			    PAGE_SIZE, 0);

		if (tx->buf[i] == NULL) {
			ioat_test_transaction_destroy(tx);
			return (NULL);
		}
	}
	return (tx);
}