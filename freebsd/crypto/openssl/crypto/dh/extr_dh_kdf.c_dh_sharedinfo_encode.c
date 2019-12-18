#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* parameter; int /*<<< orphan*/ * algorithm; } ;
typedef  TYPE_2__ X509_ALGOR ;
struct TYPE_10__ {unsigned char* data; int length; scalar_t__ flags; void* type; } ;
struct TYPE_7__ {TYPE_4__* octet_string; } ;
struct TYPE_9__ {TYPE_1__ value; void* type; } ;
typedef  TYPE_3__ ASN1_TYPE ;
typedef  TYPE_4__ ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int CMS_SharedInfo_encode (unsigned char**,TYPE_2__*,TYPE_4__*,size_t) ; 
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char*,int) ; 
 size_t DH_KDF_MAX ; 
 void* V_ASN1_OBJECT ; 
 void* V_ASN1_OCTET_STRING ; 
 void* V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  skip_asn1 (unsigned char**,long*,void*) ; 

__attribute__((used)) static int dh_sharedinfo_encode(unsigned char **pder, unsigned char **pctr,
                                ASN1_OBJECT *key_oid, size_t outlen,
                                const unsigned char *ukm, size_t ukmlen)
{
    unsigned char *p;
    int derlen;
    long tlen;
    /* "magic" value to check offset is sane */
    static unsigned char ctr[4] = { 0xF3, 0x17, 0x22, 0x53 };
    X509_ALGOR atmp;
    ASN1_OCTET_STRING ctr_oct, ukm_oct, *pukm_oct;
    ASN1_TYPE ctr_atype;
    if (ukmlen > DH_KDF_MAX || outlen > DH_KDF_MAX)
        return 0;
    ctr_oct.data = ctr;
    ctr_oct.length = 4;
    ctr_oct.flags = 0;
    ctr_oct.type = V_ASN1_OCTET_STRING;
    ctr_atype.type = V_ASN1_OCTET_STRING;
    ctr_atype.value.octet_string = &ctr_oct;
    atmp.algorithm = key_oid;
    atmp.parameter = &ctr_atype;
    if (ukm) {
        ukm_oct.type = V_ASN1_OCTET_STRING;
        ukm_oct.flags = 0;
        ukm_oct.data = (unsigned char *)ukm;
        ukm_oct.length = ukmlen;
        pukm_oct = &ukm_oct;
    } else
        pukm_oct = NULL;
    derlen = CMS_SharedInfo_encode(pder, &atmp, pukm_oct, outlen);
    if (derlen <= 0)
        return 0;
    p = *pder;
    tlen = derlen;
    if (!skip_asn1(&p, &tlen, V_ASN1_SEQUENCE))
        return 0;
    if (!skip_asn1(&p, &tlen, V_ASN1_SEQUENCE))
        return 0;
    if (!skip_asn1(&p, &tlen, V_ASN1_OBJECT))
        return 0;
    if (!skip_asn1(&p, &tlen, V_ASN1_OCTET_STRING))
        return 0;
    if (CRYPTO_memcmp(p, ctr, 4))
        return 0;
    *pctr = p;
    return derlen;
}