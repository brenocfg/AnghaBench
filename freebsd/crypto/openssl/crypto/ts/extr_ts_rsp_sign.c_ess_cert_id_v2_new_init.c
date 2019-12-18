#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_17__ {int /*<<< orphan*/ * algorithm; } ;
typedef  TYPE_2__ X509_ALGOR ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_19__ {TYPE_12__* issuer_serial; int /*<<< orphan*/  hash; TYPE_2__* hash_alg; } ;
struct TYPE_16__ {int /*<<< orphan*/ * dirn; } ;
struct TYPE_18__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int /*<<< orphan*/ * serial; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_4__ ESS_CERT_ID_V2 ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ESS_CERT_ID_V2_free (TYPE_4__*) ; 
 TYPE_4__* ESS_CERT_ID_V2_new () ; 
 TYPE_12__* ESS_ISSUER_SERIAL_new () ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  const* EVP_sha256 () ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_3__*) ; 
 TYPE_3__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int /*<<< orphan*/  TS_F_ESS_CERT_ID_V2_NEW_INIT ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ALGOR_free (TYPE_2__*) ; 
 TYPE_2__* X509_ALGOR_new () ; 
 int /*<<< orphan*/  X509_ALGOR_set_md (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * X509_NAME_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_digest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_push (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static ESS_CERT_ID_V2 *ess_cert_id_v2_new_init(const EVP_MD *hash_alg,
                                               X509 *cert, int issuer_needed)
{
    ESS_CERT_ID_V2 *cid = NULL;
    GENERAL_NAME *name = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = sizeof(hash);
    X509_ALGOR *alg = NULL;

    memset(hash, 0, sizeof(hash));

    if ((cid = ESS_CERT_ID_V2_new()) == NULL)
        goto err;

    if (hash_alg != EVP_sha256()) {
        alg = X509_ALGOR_new();
        if (alg == NULL)
            goto err;
        X509_ALGOR_set_md(alg, hash_alg);
        if (alg->algorithm == NULL)
            goto err;
        cid->hash_alg = alg;
        alg = NULL;
    } else {
        cid->hash_alg = NULL;
    }

    if (!X509_digest(cert, hash_alg, hash, &hash_len))
        goto err;

    if (!ASN1_OCTET_STRING_set(cid->hash, hash, hash_len))
        goto err;

    if (issuer_needed) {
        if ((cid->issuer_serial = ESS_ISSUER_SERIAL_new()) == NULL)
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
        cid->issuer_serial->serial =
                ASN1_INTEGER_dup(X509_get_serialNumber(cert));
        if (cid->issuer_serial->serial == NULL)
            goto err;
    }

    return cid;
 err:
    X509_ALGOR_free(alg);
    GENERAL_NAME_free(name);
    ESS_CERT_ID_V2_free(cid);
    TSerr(TS_F_ESS_CERT_ID_V2_NEW_INIT, ERR_R_MALLOC_FAILURE);
    return NULL;
}