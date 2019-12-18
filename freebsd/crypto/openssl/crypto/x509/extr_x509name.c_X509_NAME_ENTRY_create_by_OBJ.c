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
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  X509_NAME_ENTRY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_new () ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_set_data (int /*<<< orphan*/ *,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  X509_NAME_ENTRY_set_object (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

X509_NAME_ENTRY *X509_NAME_ENTRY_create_by_OBJ(X509_NAME_ENTRY **ne,
                                               const ASN1_OBJECT *obj, int type,
                                               const unsigned char *bytes,
                                               int len)
{
    X509_NAME_ENTRY *ret;

    if ((ne == NULL) || (*ne == NULL)) {
        if ((ret = X509_NAME_ENTRY_new()) == NULL)
            return NULL;
    } else
        ret = *ne;

    if (!X509_NAME_ENTRY_set_object(ret, obj))
        goto err;
    if (!X509_NAME_ENTRY_set_data(ret, type, bytes, len))
        goto err;

    if ((ne != NULL) && (*ne == NULL))
        *ne = ret;
    return ret;
 err:
    if ((ne == NULL) || (ret != *ne))
        X509_NAME_ENTRY_free(ret);
    return NULL;
}