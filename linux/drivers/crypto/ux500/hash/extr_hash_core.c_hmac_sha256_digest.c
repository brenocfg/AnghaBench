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
 int ahash_final (struct ahash_request*) ; 
 int ahash_update (struct ahash_request*) ; 
 int hmac_sha256_init (struct ahash_request*) ; 

__attribute__((used)) static int hmac_sha256_digest(struct ahash_request *req)
{
	int ret2, ret1;

	ret1 = hmac_sha256_init(req);
	if (ret1)
		goto out;

	ret1 = ahash_update(req);
	ret2 = ahash_final(req);

out:
	return ret1 ? ret1 : ret2;
}