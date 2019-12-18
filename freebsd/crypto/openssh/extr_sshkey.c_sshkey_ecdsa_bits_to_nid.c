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

/* Variables and functions */
 int NID_X9_62_prime256v1 ; 
 int NID_secp384r1 ; 
 int NID_secp521r1 ; 

int
sshkey_ecdsa_bits_to_nid(int bits)
{
	switch (bits) {
	case 256:
		return NID_X9_62_prime256v1;
	case 384:
		return NID_secp384r1;
# ifdef OPENSSL_HAS_NISTP521
	case 521:
		return NID_secp521r1;
# endif /* OPENSSL_HAS_NISTP521 */
	default:
		return -1;
	}
}