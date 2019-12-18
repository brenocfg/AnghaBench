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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GETU32 (unsigned char const*) ; 
 int /*<<< orphan*/  PUTU32 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camellia_encrypt128 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camellia_encrypt256 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void
Camellia_EncryptBlock(const int keyBitLength, 
		      const unsigned char *plaintext, 
		      const uint32_t *subkey,
		      unsigned char *ciphertext)
{
    uint32_t tmp[4];

    tmp[0] = GETU32(plaintext);
    tmp[1] = GETU32(plaintext + 4);
    tmp[2] = GETU32(plaintext + 8);
    tmp[3] = GETU32(plaintext + 12);

    switch (keyBitLength) {
    case 128:
	camellia_encrypt128(subkey, tmp);
	break;
    case 192:
	/* fall through */
    case 256:
	camellia_encrypt256(subkey, tmp);
	break;
    default:
	break;
    }

    PUTU32(ciphertext,    tmp[0]);
    PUTU32(ciphertext+4,  tmp[1]);
    PUTU32(ciphertext+8,  tmp[2]);
    PUTU32(ciphertext+12, tmp[3]);
}