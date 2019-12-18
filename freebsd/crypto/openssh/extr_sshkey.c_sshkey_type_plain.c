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
 int KEY_DSA ; 
#define  KEY_DSA_CERT 132 
 int KEY_ECDSA ; 
#define  KEY_ECDSA_CERT 131 
 int KEY_ED25519 ; 
#define  KEY_ED25519_CERT 130 
 int KEY_RSA ; 
#define  KEY_RSA_CERT 129 
 int KEY_XMSS ; 
#define  KEY_XMSS_CERT 128 

int
sshkey_type_plain(int type)
{
	switch (type) {
	case KEY_RSA_CERT:
		return KEY_RSA;
	case KEY_DSA_CERT:
		return KEY_DSA;
	case KEY_ECDSA_CERT:
		return KEY_ECDSA;
	case KEY_ED25519_CERT:
		return KEY_ED25519;
	case KEY_XMSS_CERT:
		return KEY_XMSS;
	default:
		return type;
	}
}