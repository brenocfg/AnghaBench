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
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_EXTENSION_new () ; 
 int /*<<< orphan*/  X509_EXTENSION_set_critical (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_EXTENSION_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSION_set_object (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_F_X509_EXTENSION_CREATE_BY_OBJ ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_EXTENSION *X509_EXTENSION_create_by_OBJ(X509_EXTENSION **ex,
                                             const ASN1_OBJECT *obj, int crit,
                                             ASN1_OCTET_STRING *data)
{
    X509_EXTENSION *ret;

    if ((ex == NULL) || (*ex == NULL)) {
        if ((ret = X509_EXTENSION_new()) == NULL) {
            X509err(X509_F_X509_EXTENSION_CREATE_BY_OBJ,
                    ERR_R_MALLOC_FAILURE);
            return NULL;
        }
    } else
        ret = *ex;

    if (!X509_EXTENSION_set_object(ret, obj))
        goto err;
    if (!X509_EXTENSION_set_critical(ret, crit))
        goto err;
    if (!X509_EXTENSION_set_data(ret, data))
        goto err;

    if ((ex != NULL) && (*ex == NULL))
        *ex = ret;
    return ret;
 err:
    if ((ex == NULL) || (ret != *ex))
        X509_EXTENSION_free(ret);
    return NULL;
}