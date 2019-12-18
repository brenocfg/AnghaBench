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
struct skcipher_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free_dst_sglist (struct skcipher_request*) ; 
 int /*<<< orphan*/  free_src_sglist (struct skcipher_request*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int) ; 
 int /*<<< orphan*/  skcipher_request_complete (struct skcipher_request*,int) ; 

__attribute__((used)) static void nitrox_skcipher_callback(void *arg, int err)
{
	struct skcipher_request *skreq = arg;

	free_src_sglist(skreq);
	free_dst_sglist(skreq);
	if (err) {
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	}

	skcipher_request_complete(skreq, err);
}