#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int /*<<< orphan*/ * byKey; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ OCSP_RESPID ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  V_OCSP_RESPID_KEY ; 
 int /*<<< orphan*/  X509_pubkey_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 

int OCSP_RESPID_set_by_key(OCSP_RESPID *respid, X509 *cert)
{
    ASN1_OCTET_STRING *byKey = NULL;
    unsigned char md[SHA_DIGEST_LENGTH];

    /* RFC2560 requires SHA1 */
    if (!X509_pubkey_digest(cert, EVP_sha1(), md, NULL))
        return 0;

    byKey = ASN1_OCTET_STRING_new();
    if (byKey == NULL)
        return 0;

    if (!(ASN1_OCTET_STRING_set(byKey, md, SHA_DIGEST_LENGTH))) {
        ASN1_OCTET_STRING_free(byKey);
        return 0;
    }

    respid->type = V_OCSP_RESPID_KEY;
    respid->value.byKey = byKey;

    return 1;
}