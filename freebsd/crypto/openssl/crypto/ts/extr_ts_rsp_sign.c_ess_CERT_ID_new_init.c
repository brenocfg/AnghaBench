#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_14__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  issuer; } ;
struct TYPE_13__ {TYPE_8__* issuer_serial; int /*<<< orphan*/  hash; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dirn; } ;
struct TYPE_12__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ GENERAL_NAME ;
typedef  TYPE_3__ ESS_CERT_ID ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ESS_CERT_ID_free (TYPE_3__*) ; 
 TYPE_3__* ESS_CERT_ID_new () ; 
 TYPE_8__* ESS_ISSUER_SERIAL_new () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_2__*) ; 
 TYPE_2__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TS_F_ESS_CERT_ID_NEW_INIT ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_NAME_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_check_purpose (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_push (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static ESS_CERT_ID *ess_CERT_ID_new_init(X509 *cert, int issuer_needed)
{
    ESS_CERT_ID *cid = NULL;
    GENERAL_NAME *name = NULL;
    unsigned char cert_sha1[SHA_DIGEST_LENGTH];

    /* Call for side-effect of computing hash and caching extensions */
    X509_check_purpose(cert, -1, 0);
    if ((cid = ESS_CERT_ID_new()) == NULL)
        goto err;
    X509_digest(cert, EVP_sha1(), cert_sha1, NULL);
    if (!ASN1_OCTET_STRING_set(cid->hash, cert_sha1, SHA_DIGEST_LENGTH))
        goto err;

    /* Setting the issuer/serial if requested. */
    if (issuer_needed) {
        if (cid->issuer_serial == NULL
            && (cid->issuer_serial = ESS_ISSUER_SERIAL_new()) == NULL)
            goto err;
        if ((name = GENERAL_NAME_new()) == NULL)
            goto err;
        name->type = GEN_DIRNAME;
        if ((name->d.dirn = X509_NAME_dup(X509_get_issuer_name(cert))) == NULL)
            goto err;
        if (!sk_GENERAL_NAME_push(cid->issuer_serial->issuer, name))
            goto err;
        name = NULL;            /* Ownership is lost. */
        ASN1_INTEGER_free(cid->issuer_serial->serial);
        if (!(cid->issuer_serial->serial =
              ASN1_INTEGER_dup(X509_get_serialNumber(cert))))
            goto err;
    }

    return cid;
 err:
    GENERAL_NAME_free(name);
    ESS_CERT_ID_free(cid);
    TSerr(TS_F_ESS_CERT_ID_NEW_INIT, ERR_R_MALLOC_FAILURE);
    return NULL;
}