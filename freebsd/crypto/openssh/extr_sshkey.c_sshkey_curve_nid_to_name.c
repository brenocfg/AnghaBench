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
#define  NID_X9_62_prime256v1 130 
#define  NID_secp384r1 129 
#define  NID_secp521r1 128 

const char *
sshkey_curve_nid_to_name(int nid)
{
	switch (nid) {
	case NID_X9_62_prime256v1:
		return "nistp256";
	case NID_secp384r1:
		return "nistp384";
# ifdef OPENSSL_HAS_NISTP521
	case NID_secp521r1:
		return "nistp521";
# endif /* OPENSSL_HAS_NISTP521 */
	default:
		return NULL;
	}
}