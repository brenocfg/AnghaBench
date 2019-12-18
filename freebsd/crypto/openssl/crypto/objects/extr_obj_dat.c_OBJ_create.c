#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* sn; char* ln; int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (TYPE_1__*) ; 
 scalar_t__ NID_undef ; 
 int /*<<< orphan*/  OBJ_F_OBJ_CREATE ; 
 int /*<<< orphan*/  OBJ_R_OID_EXISTS ; 
 int OBJ_add_object (TYPE_1__*) ; 
 scalar_t__ OBJ_ln2nid (char const*) ; 
 int /*<<< orphan*/  OBJ_new_nid (int) ; 
 scalar_t__ OBJ_obj2nid (TYPE_1__*) ; 
 scalar_t__ OBJ_sn2nid (char const*) ; 
 TYPE_1__* OBJ_txt2obj (char const*,int) ; 
 int /*<<< orphan*/  OBJerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int OBJ_create(const char *oid, const char *sn, const char *ln)
{
    ASN1_OBJECT *tmpoid = NULL;
    int ok = 0;

    /* Check to see if short or long name already present */
    if ((sn != NULL && OBJ_sn2nid(sn) != NID_undef)
            || (ln != NULL && OBJ_ln2nid(ln) != NID_undef)) {
        OBJerr(OBJ_F_OBJ_CREATE, OBJ_R_OID_EXISTS);
        return 0;
    }

    /* Convert numerical OID string to an ASN1_OBJECT structure */
    tmpoid = OBJ_txt2obj(oid, 1);
    if (tmpoid == NULL)
        return 0;

    /* If NID is not NID_undef then object already exists */
    if (OBJ_obj2nid(tmpoid) != NID_undef) {
        OBJerr(OBJ_F_OBJ_CREATE, OBJ_R_OID_EXISTS);
        goto err;
    }

    tmpoid->nid = OBJ_new_nid(1);
    tmpoid->sn = (char *)sn;
    tmpoid->ln = (char *)ln;

    ok = OBJ_add_object(tmpoid);

    tmpoid->sn = NULL;
    tmpoid->ln = NULL;

 err:
    ASN1_OBJECT_free(tmpoid);
    return ok;
}