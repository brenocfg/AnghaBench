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
typedef  void symmetric_key ;

/* Variables and functions */
 scalar_t__ CRYPT_OK ; 
 scalar_t__ aes_setup (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  os_free (void*) ; 
 void* os_malloc (int) ; 

void * aes_decrypt_init(const u8 *key, size_t len)
{
	symmetric_key *skey;
	skey = os_malloc(sizeof(*skey));
	if (skey == NULL)
		return NULL;
	if (aes_setup(key, len, 0, skey) != CRYPT_OK) {
		os_free(skey);
		return NULL;
	}
	return skey;
}