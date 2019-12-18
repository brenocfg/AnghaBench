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
typedef  int /*<<< orphan*/  heim_oid ;
typedef  int /*<<< orphan*/  PBE_string2key_func ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PBEWITHSHAAND128BITRC2_CBC ; 
 int /*<<< orphan*/  ASN1_OID_ID_PBEWITHSHAAND128BITRC4 ; 
 int /*<<< orphan*/  ASN1_OID_ID_PBEWITHSHAAND3_KEYTRIPLEDES_CBC ; 
 int /*<<< orphan*/  ASN1_OID_ID_PBEWITHSHAAND40BITRC2_CBC ; 
 int /*<<< orphan*/  ASN1_OID_ID_PBEWITHSHAAND40BITRC4 ; 
 int /*<<< orphan*/  const* ASN1_OID_ID_PKCS3_DES_EDE3_CBC ; 
 int /*<<< orphan*/  const* ASN1_OID_ID_PKCS3_RC2_CBC ; 
 int /*<<< orphan*/  const* ASN1_OID_ID_PKCS3_RC4 ; 
 int /*<<< orphan*/ * EVP_des_ede3_cbc () ; 
 int /*<<< orphan*/ * EVP_rc2_40_cbc () ; 
 int /*<<< orphan*/ * EVP_rc2_cbc () ; 
 int /*<<< orphan*/ * EVP_rc4 () ; 
 int /*<<< orphan*/ * EVP_rc4_40 () ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/  PBE_string2key ; 
 int /*<<< orphan*/  const asn1_oid_private_rc2_40 ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const heim_oid *
find_string2key(const heim_oid *oid,
		const EVP_CIPHER **c,
		const EVP_MD **md,
		PBE_string2key_func *s2k)
{
    if (der_heim_oid_cmp(oid, ASN1_OID_ID_PBEWITHSHAAND40BITRC2_CBC) == 0) {
	*c = EVP_rc2_40_cbc();
	*md = EVP_sha1();
	*s2k = PBE_string2key;
	return &asn1_oid_private_rc2_40;
    } else if (der_heim_oid_cmp(oid, ASN1_OID_ID_PBEWITHSHAAND128BITRC2_CBC) == 0) {
	*c = EVP_rc2_cbc();
	*md = EVP_sha1();
	*s2k = PBE_string2key;
	return ASN1_OID_ID_PKCS3_RC2_CBC;
#if 0
    } else if (der_heim_oid_cmp(oid, ASN1_OID_ID_PBEWITHSHAAND40BITRC4) == 0) {
	*c = EVP_rc4_40();
	*md = EVP_sha1();
	*s2k = PBE_string2key;
	return NULL;
    } else if (der_heim_oid_cmp(oid, ASN1_OID_ID_PBEWITHSHAAND128BITRC4) == 0) {
	*c = EVP_rc4();
	*md = EVP_sha1();
	*s2k = PBE_string2key;
	return ASN1_OID_ID_PKCS3_RC4;
#endif
    } else if (der_heim_oid_cmp(oid, ASN1_OID_ID_PBEWITHSHAAND3_KEYTRIPLEDES_CBC) == 0) {
	*c = EVP_des_ede3_cbc();
	*md = EVP_sha1();
	*s2k = PBE_string2key;
	return ASN1_OID_ID_PKCS3_DES_EDE3_CBC;
    }

    return NULL;
}