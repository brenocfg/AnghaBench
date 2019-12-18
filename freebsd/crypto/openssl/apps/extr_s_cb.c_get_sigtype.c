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
#define  EVP_PKEY_DSA 136 
#define  EVP_PKEY_EC 135 
#define  EVP_PKEY_RSA 134 
#define  EVP_PKEY_RSA_PSS 133 
#define  NID_ED25519 132 
#define  NID_ED448 131 
#define  NID_id_GostR3410_2001 130 
#define  NID_id_GostR3410_2012_256 129 
#define  NID_id_GostR3410_2012_512 128 

__attribute__((used)) static const char *get_sigtype(int nid)
{
    switch (nid) {
    case EVP_PKEY_RSA:
        return "RSA";

    case EVP_PKEY_RSA_PSS:
        return "RSA-PSS";

    case EVP_PKEY_DSA:
        return "DSA";

     case EVP_PKEY_EC:
        return "ECDSA";

     case NID_ED25519:
        return "Ed25519";

     case NID_ED448:
        return "Ed448";

     case NID_id_GostR3410_2001:
        return "gost2001";

     case NID_id_GostR3410_2012_256:
        return "gost2012_256";

     case NID_id_GostR3410_2012_512:
        return "gost2012_512";

    default:
        return NULL;
    }
}