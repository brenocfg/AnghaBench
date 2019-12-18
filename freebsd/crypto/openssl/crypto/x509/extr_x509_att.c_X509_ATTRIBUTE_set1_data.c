#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  set; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ X509_ATTRIBUTE ;
struct TYPE_10__ {int type; } ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  TYPE_2__ ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ASN1_STRING_set (TYPE_2__*,void const*,int) ; 
 TYPE_2__* ASN1_STRING_set_by_NID (int /*<<< orphan*/ *,void const*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* ASN1_STRING_type_new (int) ; 
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ASN1_TYPE_set1 (int /*<<< orphan*/ *,int,void const*) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int MBSTRING_FLAG ; 
 int /*<<< orphan*/  OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_F_X509_ATTRIBUTE_SET1_DATA ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ASN1_TYPE_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int X509_ATTRIBUTE_set1_data(X509_ATTRIBUTE *attr, int attrtype,
                             const void *data, int len)
{
    ASN1_TYPE *ttmp = NULL;
    ASN1_STRING *stmp = NULL;
    int atype = 0;
    if (!attr)
        return 0;
    if (attrtype & MBSTRING_FLAG) {
        stmp = ASN1_STRING_set_by_NID(NULL, data, len, attrtype,
                                      OBJ_obj2nid(attr->object));
        if (!stmp) {
            X509err(X509_F_X509_ATTRIBUTE_SET1_DATA, ERR_R_ASN1_LIB);
            return 0;
        }
        atype = stmp->type;
    } else if (len != -1) {
        if ((stmp = ASN1_STRING_type_new(attrtype)) == NULL)
            goto err;
        if (!ASN1_STRING_set(stmp, data, len))
            goto err;
        atype = attrtype;
    }
    /*
     * This is a bit naughty because the attribute should really have at
     * least one value but some types use and zero length SET and require
     * this.
     */
    if (attrtype == 0) {
        ASN1_STRING_free(stmp);
        return 1;
    }
    if ((ttmp = ASN1_TYPE_new()) == NULL)
        goto err;
    if ((len == -1) && !(attrtype & MBSTRING_FLAG)) {
        if (!ASN1_TYPE_set1(ttmp, attrtype, data))
            goto err;
    } else {
        ASN1_TYPE_set(ttmp, atype, stmp);
        stmp = NULL;
    }
    if (!sk_ASN1_TYPE_push(attr->set, ttmp))
        goto err;
    return 1;
 err:
    X509err(X509_F_X509_ATTRIBUTE_SET1_DATA, ERR_R_MALLOC_FAILURE);
    ASN1_TYPE_free(ttmp);
    ASN1_STRING_free(stmp);
    return 0;
}