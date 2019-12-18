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
typedef  int krb5_enctype ;

/* Variables and functions */
#define  ETYPE_ARCFOUR_HMAC_MD5 136 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 135 
#define  ETYPE_ARCFOUR_HMAC_OLD 134 
#define  ETYPE_ARCFOUR_HMAC_OLD_EXP 133 
#define  ETYPE_ARCFOUR_MD4 132 
#define  ETYPE_DES3_CBC_SHA1 131 
#define  ETYPE_DES_CBC_CRC 130 
#define  ETYPE_DES_CBC_MD4 129 
#define  ETYPE_DES_CBC_MD5 128 

__attribute__((used)) static int
older_enctype(krb5_enctype enctype)
{
    switch (enctype) {
    case ETYPE_DES_CBC_CRC:
    case ETYPE_DES_CBC_MD4:
    case ETYPE_DES_CBC_MD5:
    case ETYPE_DES3_CBC_SHA1:
    case ETYPE_ARCFOUR_HMAC_MD5:
    case ETYPE_ARCFOUR_HMAC_MD5_56:
    /*
     * The following three is "old" windows enctypes and is needed for
     * windows 2000 hosts.
     */
    case ETYPE_ARCFOUR_MD4:
    case ETYPE_ARCFOUR_HMAC_OLD:
    case ETYPE_ARCFOUR_HMAC_OLD_EXP:
	return 1;
    default:
	return 0;
    }
}