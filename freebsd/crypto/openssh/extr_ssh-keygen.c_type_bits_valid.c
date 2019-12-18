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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ DEFAULT_BITS ; 
 scalar_t__ DEFAULT_BITS_DSA ; 
 scalar_t__ DEFAULT_BITS_ECDSA ; 
#define  KEY_DSA 130 
#define  KEY_ECDSA 129 
#define  KEY_RSA 128 
 int KEY_UNSPEC ; 
 scalar_t__ OPENSSL_DSA_MAX_MODULUS_BITS ; 
 scalar_t__ OPENSSL_RSA_MAX_MODULUS_BITS ; 
 scalar_t__ SSH_RSA_MINIMUM_MODULUS_SIZE ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  key_type_name ; 
 scalar_t__ sshkey_curve_nid_to_bits (scalar_t__) ; 
 int sshkey_ecdsa_bits_to_nid (scalar_t__) ; 
 scalar_t__ sshkey_ecdsa_nid_from_name (char const*) ; 

__attribute__((used)) static void
type_bits_valid(int type, const char *name, u_int32_t *bitsp)
{
#ifdef WITH_OPENSSL
	u_int maxbits, nid;
#endif

	if (type == KEY_UNSPEC)
		fatal("unknown key type %s", key_type_name);
	if (*bitsp == 0) {
#ifdef WITH_OPENSSL
		if (type == KEY_DSA)
			*bitsp = DEFAULT_BITS_DSA;
		else if (type == KEY_ECDSA) {
			if (name != NULL &&
			    (nid = sshkey_ecdsa_nid_from_name(name)) > 0)
				*bitsp = sshkey_curve_nid_to_bits(nid);
			if (*bitsp == 0)
				*bitsp = DEFAULT_BITS_ECDSA;
		} else
#endif
			*bitsp = DEFAULT_BITS;
	}
#ifdef WITH_OPENSSL
	maxbits = (type == KEY_DSA) ?
	    OPENSSL_DSA_MAX_MODULUS_BITS : OPENSSL_RSA_MAX_MODULUS_BITS;
	if (*bitsp > maxbits)
		fatal("key bits exceeds maximum %d", maxbits);
	switch (type) {
	case KEY_DSA:
		if (*bitsp != 1024)
			fatal("Invalid DSA key length: must be 1024 bits");
		break;
	case KEY_RSA:
		if (*bitsp < SSH_RSA_MINIMUM_MODULUS_SIZE)
			fatal("Invalid RSA key length: minimum is %d bits",
			    SSH_RSA_MINIMUM_MODULUS_SIZE);
		break;
	case KEY_ECDSA:
		if (sshkey_ecdsa_bits_to_nid(*bitsp) == -1)
			fatal("Invalid ECDSA key length: valid lengths are "
			    "256, 384 or 521 bits");
	}
#endif
}