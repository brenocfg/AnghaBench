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
struct asn1_oid {int dummy; } ;
typedef  enum pkcs5_alg { ____Placeholder_pkcs5_alg } pkcs5_alg ;

/* Variables and functions */
 int PKCS5_ALG_MD5_DES_CBC ; 
 int PKCS5_ALG_PBES2 ; 
 int PKCS5_ALG_SHA1_3DES_CBC ; 
 int PKCS5_ALG_UNKNOWN ; 
 scalar_t__ pkcs12_is_pbe_oid (struct asn1_oid*,int) ; 
 scalar_t__ pkcs5_is_oid (struct asn1_oid*,int) ; 

__attribute__((used)) static enum pkcs5_alg pkcs5_get_alg(struct asn1_oid *oid)
{
	if (pkcs5_is_oid(oid, 3)) /* pbeWithMD5AndDES-CBC (PBES1) */
		return PKCS5_ALG_MD5_DES_CBC;
	if (pkcs12_is_pbe_oid(oid, 3)) /* pbeWithSHAAnd3-KeyTripleDES-CBC */
		return PKCS5_ALG_SHA1_3DES_CBC;
	if (pkcs5_is_oid(oid, 13)) /* id-PBES2 (PBES2) */
		return PKCS5_ALG_PBES2;
	return PKCS5_ALG_UNKNOWN;
}