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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ CRYPTO_AES_CBC ; 
 scalar_t__ CRYPTO_AES_XTS ; 
 int g_eli_crypto_cipher (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t) ; 

int
g_eli_crypto_decrypt(u_int algo, u_char *data, size_t datasize,
    const u_char *key, size_t keysize)
{

	/* We prefer AES-CBC for metadata protection. */
	if (algo == CRYPTO_AES_XTS)
		algo = CRYPTO_AES_CBC;

	return (g_eli_crypto_cipher(algo, 0, data, datasize, key, keysize));
}