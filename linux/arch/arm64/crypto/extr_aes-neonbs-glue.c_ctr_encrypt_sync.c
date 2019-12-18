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
 int crypto_ctr_encrypt_walk (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 int ctr_encrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  ctr_encrypt_one ; 

__attribute__((used)) static int ctr_encrypt_sync(struct skcipher_request *req)
{
	if (!crypto_simd_usable())
		return crypto_ctr_encrypt_walk(req, ctr_encrypt_one);

	return ctr_encrypt(req);
}