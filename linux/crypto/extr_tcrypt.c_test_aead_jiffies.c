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
struct aead_request {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  crypto_aead_decrypt (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_aead_encrypt (struct aead_request*) ; 
 int do_one_aead_op (struct aead_request*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  printk (char*,int,int,long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int test_aead_jiffies(struct aead_request *req, int enc,
				int blen, int secs)
{
	unsigned long start, end;
	int bcount;
	int ret;

	for (start = jiffies, end = start + secs * HZ, bcount = 0;
	     time_before(jiffies, end); bcount++) {
		if (enc)
			ret = do_one_aead_op(req, crypto_aead_encrypt(req));
		else
			ret = do_one_aead_op(req, crypto_aead_decrypt(req));

		if (ret)
			return ret;
	}

	printk("%d operations in %d seconds (%ld bytes)\n",
	       bcount, secs, (long)bcount * blen);
	return 0;
}