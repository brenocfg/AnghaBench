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
typedef  int u32 ;
struct test_mb_ahash_data {int /*<<< orphan*/  wait; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int crypto_ahash_digest (int /*<<< orphan*/ ) ; 
 int crypto_wait_req (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static inline int do_mult_ahash_op(struct test_mb_ahash_data *data, u32 num_mb,
				   int *rc)
{
	int i, err = 0;

	/* Fire up a bunch of concurrent requests */
	for (i = 0; i < num_mb; i++)
		rc[i] = crypto_ahash_digest(data[i].req);

	/* Wait for all requests to finish */
	for (i = 0; i < num_mb; i++) {
		rc[i] = crypto_wait_req(rc[i], &data[i].wait);

		if (rc[i]) {
			pr_info("concurrent request %d error %d\n", i, rc[i]);
			err = rc[i];
		}
	}

	return err;
}