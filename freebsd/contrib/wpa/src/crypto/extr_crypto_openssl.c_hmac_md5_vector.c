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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_md5 () ; 
 int openssl_hmac_vector (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ *,int) ; 

int hmac_md5_vector(const u8 *key, size_t key_len, size_t num_elem,
		    const u8 *addr[], const size_t *len, u8 *mac)
{
	return openssl_hmac_vector(EVP_md5(), key ,key_len, num_elem, addr, len,
				   mac, 16);
}