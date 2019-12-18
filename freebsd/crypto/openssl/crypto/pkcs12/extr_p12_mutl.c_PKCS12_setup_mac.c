#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_8__ {int /*<<< orphan*/  dinfo; TYPE_1__* salt; int /*<<< orphan*/ * iter; } ;
struct TYPE_7__ {TYPE_4__* mac; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ PKCS12 ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int PKCS12_ERROR ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_SETUP_MAC ; 
 int /*<<< orphan*/  PKCS12_MAC_DATA_free (TYPE_4__*) ; 
 TYPE_4__* PKCS12_MAC_DATA_new () ; 
 int PKCS12_SALT_LEN ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_getm (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

int PKCS12_setup_mac(PKCS12 *p12, int iter, unsigned char *salt, int saltlen,
                     const EVP_MD *md_type)
{
    X509_ALGOR *macalg;

    PKCS12_MAC_DATA_free(p12->mac);
    p12->mac = NULL;

    if ((p12->mac = PKCS12_MAC_DATA_new()) == NULL)
        return PKCS12_ERROR;
    if (iter > 1) {
        if ((p12->mac->iter = ASN1_INTEGER_new()) == NULL) {
            PKCS12err(PKCS12_F_PKCS12_SETUP_MAC, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        if (!ASN1_INTEGER_set(p12->mac->iter, iter)) {
            PKCS12err(PKCS12_F_PKCS12_SETUP_MAC, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    }
    if (!saltlen)
        saltlen = PKCS12_SALT_LEN;
    if ((p12->mac->salt->data = OPENSSL_malloc(saltlen)) == NULL) {
        PKCS12err(PKCS12_F_PKCS12_SETUP_MAC, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    p12->mac->salt->length = saltlen;
    if (!salt) {
        if (RAND_bytes(p12->mac->salt->data, saltlen) <= 0)
            return 0;
    } else
        memcpy(p12->mac->salt->data, salt, saltlen);
    X509_SIG_getm(p12->mac->dinfo, &macalg, NULL);
    if (!X509_ALGOR_set0(macalg, OBJ_nid2obj(EVP_MD_type(md_type)),
                         V_ASN1_NULL, NULL)) {
        PKCS12err(PKCS12_F_PKCS12_SETUP_MAC, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    return 1;
}