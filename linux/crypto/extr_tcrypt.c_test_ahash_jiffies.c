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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  crypto_ahash_final (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_init (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int do_one_ahash_op (struct ahash_request*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_cont (char*,int,long) ; 
 int test_ahash_jiffies_digest (struct ahash_request*,int,char*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int test_ahash_jiffies(struct ahash_request *req, int blen,
			      int plen, char *out, int secs)
{
	unsigned long start, end;
	int bcount, pcount;
	int ret;

	if (plen == blen)
		return test_ahash_jiffies_digest(req, blen, out, secs);

	for (start = jiffies, end = start + secs * HZ, bcount = 0;
	     time_before(jiffies, end); bcount++) {
		ret = do_one_ahash_op(req, crypto_ahash_init(req));
		if (ret)
			return ret;
		for (pcount = 0; pcount < blen; pcount += plen) {
			ret = do_one_ahash_op(req, crypto_ahash_update(req));
			if (ret)
				return ret;
		}
		/* we assume there is enough space in 'out' for the result */
		ret = do_one_ahash_op(req, crypto_ahash_final(req));
		if (ret)
			return ret;
	}

	pr_cont("%6u opers/sec, %9lu bytes/sec\n",
		bcount / secs, ((long)bcount * blen) / secs);

	return 0;
}