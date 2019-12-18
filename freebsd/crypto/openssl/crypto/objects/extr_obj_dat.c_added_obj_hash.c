#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; TYPE_1__* obj; } ;
struct TYPE_4__ {long length; unsigned long nid; int /*<<< orphan*/  ln; int /*<<< orphan*/  sn; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;
typedef  TYPE_2__ ADDED_OBJ ;

/* Variables and functions */
#define  ADDED_DATA 131 
#define  ADDED_LNAME 130 
#define  ADDED_NID 129 
#define  ADDED_SNAME 128 
 unsigned long OPENSSL_LH_strhash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long added_obj_hash(const ADDED_OBJ *ca)
{
    const ASN1_OBJECT *a;
    int i;
    unsigned long ret = 0;
    unsigned char *p;

    a = ca->obj;
    switch (ca->type) {
    case ADDED_DATA:
        ret = a->length << 20L;
        p = (unsigned char *)a->data;
        for (i = 0; i < a->length; i++)
            ret ^= p[i] << ((i * 3) % 24);
        break;
    case ADDED_SNAME:
        ret = OPENSSL_LH_strhash(a->sn);
        break;
    case ADDED_LNAME:
        ret = OPENSSL_LH_strhash(a->ln);
        break;
    case ADDED_NID:
        ret = a->nid;
        break;
    default:
        /* abort(); */
        return 0;
    }
    ret &= 0x3fffffffL;
    ret |= ((unsigned long)ca->type) << 30L;
    return ret;
}