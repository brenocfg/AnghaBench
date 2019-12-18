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
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_ATTRIBUTE_create_by_OBJ (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  X509_F_X509_ATTRIBUTE_CREATE_BY_TXT ; 
 int /*<<< orphan*/  X509_R_INVALID_FIELD_NAME ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

X509_ATTRIBUTE *X509_ATTRIBUTE_create_by_txt(X509_ATTRIBUTE **attr,
                                             const char *atrname, int type,
                                             const unsigned char *bytes,
                                             int len)
{
    ASN1_OBJECT *obj;
    X509_ATTRIBUTE *nattr;

    obj = OBJ_txt2obj(atrname, 0);
    if (obj == NULL) {
        X509err(X509_F_X509_ATTRIBUTE_CREATE_BY_TXT,
                X509_R_INVALID_FIELD_NAME);
        ERR_add_error_data(2, "name=", atrname);
        return NULL;
    }
    nattr = X509_ATTRIBUTE_create_by_OBJ(attr, obj, type, bytes, len);
    ASN1_OBJECT_free(obj);
    return nattr;
}