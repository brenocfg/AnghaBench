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
struct ahash_request {int dummy; } ;
typedef  scalar_t__ cycles_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 
 int do_one_ahash_op (struct ahash_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  pr_cont (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int test_ahash_cycles_digest(struct ahash_request *req, int blen,
				    char *out)
{
	unsigned long cycles = 0;
	int ret, i;

	/* Warm-up run. */
	for (i = 0; i < 4; i++) {
		ret = do_one_ahash_op(req, crypto_ahash_digest(req));
		if (ret)
			goto out;
	}

	/* The real thing. */
	for (i = 0; i < 8; i++) {
		cycles_t start, end;

		start = get_cycles();

		ret = do_one_ahash_op(req, crypto_ahash_digest(req));
		if (ret)
			goto out;

		end = get_cycles();

		cycles += end - start;
	}

out:
	if (ret)
		return ret;

	pr_cont("%6lu cycles/operation, %4lu cycles/byte\n",
		cycles / 8, cycles / (8 * blen));

	return 0;
}