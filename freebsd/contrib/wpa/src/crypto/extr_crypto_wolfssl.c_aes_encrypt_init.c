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
typedef  void Aes ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ENCRYPTION ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  os_free (void*) ; 
 void* os_malloc (int) ; 
 scalar_t__ wc_AesSetKey (void*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void * aes_encrypt_init(const u8 *key, size_t len)
{
	Aes *aes;

	if (TEST_FAIL())
		return NULL;

	aes = os_malloc(sizeof(Aes));
	if (!aes)
		return NULL;

	if (wc_AesSetKey(aes, key, len, NULL, AES_ENCRYPTION) < 0) {
		os_free(aes);
		return NULL;
	}

	return aes;
}