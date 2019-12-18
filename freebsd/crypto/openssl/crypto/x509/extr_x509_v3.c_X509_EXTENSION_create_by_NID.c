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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int /*<<< orphan*/ * X509_EXTENSION_create_by_OBJ (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_F_X509_EXTENSION_CREATE_BY_NID ; 
 int /*<<< orphan*/  X509_R_UNKNOWN_NID ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_EXTENSION *X509_EXTENSION_create_by_NID(X509_EXTENSION **ex, int nid,
                                             int crit,
                                             ASN1_OCTET_STRING *data)
{
    ASN1_OBJECT *obj;
    X509_EXTENSION *ret;

    obj = OBJ_nid2obj(nid);
    if (obj == NULL) {
        X509err(X509_F_X509_EXTENSION_CREATE_BY_NID, X509_R_UNKNOWN_NID);
        return NULL;
    }
    ret = X509_EXTENSION_create_by_OBJ(ex, obj, crit, data);
    if (ret == NULL)
        ASN1_OBJECT_free(obj);
    return ret;
}