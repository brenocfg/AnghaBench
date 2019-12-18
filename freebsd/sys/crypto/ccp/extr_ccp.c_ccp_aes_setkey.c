#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int key_len; int /*<<< orphan*/  enckey; int /*<<< orphan*/  cipher_type; } ;
struct ccp_session {TYPE_1__ blkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_AES_TYPE_128 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_192 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_256 ; 
 int CRYPTO_AES_XTS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ccp_aes_setkey(struct ccp_session *s, int alg, const void *key, int klen)
{
	unsigned kbits;

	if (alg == CRYPTO_AES_XTS)
		kbits = klen / 2;
	else
		kbits = klen;

	switch (kbits) {
	case 128:
		s->blkcipher.cipher_type = CCP_AES_TYPE_128;
		break;
	case 192:
		s->blkcipher.cipher_type = CCP_AES_TYPE_192;
		break;
	case 256:
		s->blkcipher.cipher_type = CCP_AES_TYPE_256;
		break;
	default:
		panic("should not get here");
	}

	s->blkcipher.key_len = klen / 8;
	memcpy(s->blkcipher.enckey, key, s->blkcipher.key_len);
}