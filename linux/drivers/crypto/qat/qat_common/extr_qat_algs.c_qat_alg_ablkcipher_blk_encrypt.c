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
struct ablkcipher_request {int nbytes; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int EINVAL ; 
 int qat_alg_ablkcipher_encrypt (struct ablkcipher_request*) ; 

__attribute__((used)) static int qat_alg_ablkcipher_blk_encrypt(struct ablkcipher_request *req)
{
	if (req->nbytes % AES_BLOCK_SIZE != 0)
		return -EINVAL;

	return qat_alg_ablkcipher_encrypt(req);
}