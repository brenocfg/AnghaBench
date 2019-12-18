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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct test_transaction {int depth; char** buf; int length; struct ioat_test* test; } ;
struct ioat_test {scalar_t__ testkind; char* raw_vtarget; scalar_t__ raw_write; } ;

/* Variables and functions */
 scalar_t__ IOAT_TEST_DMA ; 
 scalar_t__ IOAT_TEST_FILL ; 
 scalar_t__ IOAT_TEST_RAW_DMA ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  dump_hex (char*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static bool
ioat_compare_ok(struct test_transaction *tx)
{
	struct ioat_test *test;
	char *dst, *src;
	uint32_t i, j;

	test = tx->test;

	for (i = 0; i < tx->depth; i++) {
		dst = tx->buf[2 * i + 1];
		src = tx->buf[2 * i];

		if (test->testkind == IOAT_TEST_FILL) {
			for (j = 0; j < tx->length; j += sizeof(uint64_t)) {
				if (memcmp(src, &dst[j],
					MIN(sizeof(uint64_t), tx->length - j))
				    != 0)
					return (false);
			}
		} else if (test->testkind == IOAT_TEST_DMA) {
			if (memcmp(src, dst, tx->length) != 0)
				return (false);
		} else if (test->testkind == IOAT_TEST_RAW_DMA) {
			if (test->raw_write)
				dst = test->raw_vtarget;
			dump_hex(dst, tx->length / 32);
		}
	}
	return (true);
}