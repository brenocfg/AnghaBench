#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* authsafes; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ PKCS12 ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
#define  NID_pkcs7_data 128 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_INIT ; 
 int /*<<< orphan*/  PKCS12_R_UNSUPPORTED_PKCS12_MODE ; 
 int /*<<< orphan*/  PKCS12_free (TYPE_3__*) ; 
 TYPE_3__* PKCS12_new () ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PKCS12 *PKCS12_init(int mode)
{
    PKCS12 *pkcs12;

    if ((pkcs12 = PKCS12_new()) == NULL) {
        PKCS12err(PKCS12_F_PKCS12_INIT, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    if (!ASN1_INTEGER_set(pkcs12->version, 3))
        goto err;
    pkcs12->authsafes->type = OBJ_nid2obj(mode);
    switch (mode) {
    case NID_pkcs7_data:
        if ((pkcs12->authsafes->d.data = ASN1_OCTET_STRING_new()) == NULL) {
            PKCS12err(PKCS12_F_PKCS12_INIT, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        break;
    default:
        PKCS12err(PKCS12_F_PKCS12_INIT, PKCS12_R_UNSUPPORTED_PKCS12_MODE);
        goto err;
    }
    return pkcs12;

 err:
    PKCS12_free(pkcs12);
    return NULL;
}