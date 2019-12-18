#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_7__ {int /*<<< orphan*/  byKey; int /*<<< orphan*/  byName; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ value; } ;
struct TYPE_6__ {TYPE_3__ responderId; } ;
struct TYPE_9__ {TYPE_1__ tbsResponseData; } ;
typedef  TYPE_3__ OCSP_RESPID ;
typedef  TYPE_4__ OCSP_BASICRESP ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_OCTET_STRING_dup (int /*<<< orphan*/ ) ; 
 scalar_t__ V_OCSP_RESPID_KEY ; 
 scalar_t__ V_OCSP_RESPID_NAME ; 
 int /*<<< orphan*/ * X509_NAME_dup (int /*<<< orphan*/ ) ; 

int OCSP_resp_get1_id(const OCSP_BASICRESP *bs,
                      ASN1_OCTET_STRING **pid,
                      X509_NAME **pname)
{
    const OCSP_RESPID *rid = &bs->tbsResponseData.responderId;

    if (rid->type == V_OCSP_RESPID_NAME) {
        *pname = X509_NAME_dup(rid->value.byName);
        *pid = NULL;
    } else if (rid->type == V_OCSP_RESPID_KEY) {
        *pid = ASN1_OCTET_STRING_dup(rid->value.byKey);
        *pname = NULL;
    } else {
        return 0;
    }
    if (*pname == NULL && *pid == NULL)
        return 0;
    return 1;
}