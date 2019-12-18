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
typedef  int /*<<< orphan*/  X509_ATTRIBUTE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509_ATTRIBUTE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_ATTRIBUTE_new () ; 
 int /*<<< orphan*/  X509_ATTRIBUTE_set1_data (int /*<<< orphan*/ *,int,void const*,int) ; 
 int /*<<< orphan*/  X509_ATTRIBUTE_set1_object (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_F_X509_ATTRIBUTE_CREATE_BY_OBJ ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_ATTRIBUTE *X509_ATTRIBUTE_create_by_OBJ(X509_ATTRIBUTE **attr,
                                             const ASN1_OBJECT *obj,
                                             int atrtype, const void *data,
                                             int len)
{
    X509_ATTRIBUTE *ret;

    if ((attr == NULL) || (*attr == NULL)) {
        if ((ret = X509_ATTRIBUTE_new()) == NULL) {
            X509err(X509_F_X509_ATTRIBUTE_CREATE_BY_OBJ,
                    ERR_R_MALLOC_FAILURE);
            return NULL;
        }
    } else
        ret = *attr;

    if (!X509_ATTRIBUTE_set1_object(ret, obj))
        goto err;
    if (!X509_ATTRIBUTE_set1_data(ret, atrtype, data, len))
        goto err;

    if ((attr != NULL) && (*attr == NULL))
        *attr = ret;
    return ret;
 err:
    if ((attr == NULL) || (ret != *attr))
        X509_ATTRIBUTE_free(ret);
    return NULL;
}