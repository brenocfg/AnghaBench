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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hash_type { ____Placeholder_hash_type } hash_type ;
typedef  enum hash_alg { ____Placeholder_hash_alg } hash_alg ;

/* Variables and functions */
 int HASH_ALG_SHA224 ; 
 int HASH_ALG_SHA384 ; 
 int HASH_TYPE_INIT ; 
 int HASH_TYPE_UPDT ; 
 int /*<<< orphan*/  SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 

u32 spum_digest_size(u32 alg_digest_size, enum hash_alg alg,
		     enum hash_type htype)
{
	u32 digestsize = alg_digest_size;

	/* SPU returns complete digest when doing incremental hash and truncated
	 * hash algo.
	 */
	if ((htype == HASH_TYPE_INIT) || (htype == HASH_TYPE_UPDT)) {
		if (alg == HASH_ALG_SHA224)
			digestsize = SHA256_DIGEST_SIZE;
		else if (alg == HASH_ALG_SHA384)
			digestsize = SHA512_DIGEST_SIZE;
	}
	return digestsize;
}