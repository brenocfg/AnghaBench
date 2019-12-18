#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nid; unsigned char const* data; int length; int flags; int /*<<< orphan*/ * ln; int /*<<< orphan*/ * sn; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_C2I_ASN1_OBJECT ; 
 int ASN1_OBJECT_FLAG_DYNAMIC ; 
 int ASN1_OBJECT_FLAG_DYNAMIC_DATA ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OBJECT_new () ; 
 int ASN1_R_INVALID_OBJECT_ENCODING ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int) ; 
 int ERR_R_MALLOC_FAILURE ; 
 long INT_MAX ; 
 int NID_undef ; 
 TYPE_1__* OBJ_nid2obj (int) ; 
 int OBJ_obj2nid (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

ASN1_OBJECT *c2i_ASN1_OBJECT(ASN1_OBJECT **a, const unsigned char **pp,
                             long len)
{
    ASN1_OBJECT *ret = NULL, tobj;
    const unsigned char *p;
    unsigned char *data;
    int i, length;

    /*
     * Sanity check OID encoding. Need at least one content octet. MSB must
     * be clear in the last octet. can't have leading 0x80 in subidentifiers,
     * see: X.690 8.19.2
     */
    if (len <= 0 || len > INT_MAX || pp == NULL || (p = *pp) == NULL ||
        p[len - 1] & 0x80) {
        ASN1err(ASN1_F_C2I_ASN1_OBJECT, ASN1_R_INVALID_OBJECT_ENCODING);
        return NULL;
    }
    /* Now 0 < len <= INT_MAX, so the cast is safe. */
    length = (int)len;
    /*
     * Try to lookup OID in table: these are all valid encodings so if we get
     * a match we know the OID is valid.
     */
    tobj.nid = NID_undef;
    tobj.data = p;
    tobj.length = length;
    tobj.flags = 0;
    i = OBJ_obj2nid(&tobj);
    if (i != NID_undef) {
        /*
         * Return shared registered OID object: this improves efficiency
         * because we don't have to return a dynamically allocated OID
         * and NID lookups can use the cached value.
         */
        ret = OBJ_nid2obj(i);
        if (a) {
            ASN1_OBJECT_free(*a);
            *a = ret;
        }
        *pp += len;
        return ret;
    }
    for (i = 0; i < length; i++, p++) {
        if (*p == 0x80 && (!i || !(p[-1] & 0x80))) {
            ASN1err(ASN1_F_C2I_ASN1_OBJECT, ASN1_R_INVALID_OBJECT_ENCODING);
            return NULL;
        }
    }

    /*
     * only the ASN1_OBJECTs from the 'table' will have values for ->sn or
     * ->ln
     */
    if ((a == NULL) || ((*a) == NULL) ||
        !((*a)->flags & ASN1_OBJECT_FLAG_DYNAMIC)) {
        if ((ret = ASN1_OBJECT_new()) == NULL)
            return NULL;
    } else
        ret = (*a);

    p = *pp;
    /* detach data from object */
    data = (unsigned char *)ret->data;
    ret->data = NULL;
    /* once detached we can change it */
    if ((data == NULL) || (ret->length < length)) {
        ret->length = 0;
        OPENSSL_free(data);
        data = OPENSSL_malloc(length);
        if (data == NULL) {
            i = ERR_R_MALLOC_FAILURE;
            goto err;
        }
        ret->flags |= ASN1_OBJECT_FLAG_DYNAMIC_DATA;
    }
    memcpy(data, p, length);
    /* reattach data to object, after which it remains const */
    ret->data = data;
    ret->length = length;
    ret->sn = NULL;
    ret->ln = NULL;
    /* ret->flags=ASN1_OBJECT_FLAG_DYNAMIC; we know it is dynamic */
    p += length;

    if (a != NULL)
        (*a) = ret;
    *pp = p;
    return ret;
 err:
    ASN1err(ASN1_F_C2I_ASN1_OBJECT, i);
    if ((a == NULL) || (*a != ret))
        ASN1_OBJECT_free(ret);
    return NULL;
}