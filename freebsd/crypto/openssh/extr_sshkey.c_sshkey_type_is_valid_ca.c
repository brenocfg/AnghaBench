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
#define  KEY_DSA 132 
#define  KEY_ECDSA 131 
#define  KEY_ED25519 130 
#define  KEY_RSA 129 
#define  KEY_XMSS 128 

__attribute__((used)) static int
sshkey_type_is_valid_ca(int type)
{
	switch (type) {
	case KEY_RSA:
	case KEY_DSA:
	case KEY_ECDSA:
	case KEY_ED25519:
	case KEY_XMSS:
		return 1;
	default:
		return 0;
	}
}