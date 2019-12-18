#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; TYPE_1__* obj; } ;
struct TYPE_5__ {int length; int nid; int /*<<< orphan*/ * ln; int /*<<< orphan*/ * sn; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;
typedef  TYPE_2__ ADDED_OBJ ;

/* Variables and functions */
#define  ADDED_DATA 131 
#define  ADDED_LNAME 130 
#define  ADDED_NID 129 
#define  ADDED_SNAME 128 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int added_obj_cmp(const ADDED_OBJ *ca, const ADDED_OBJ *cb)
{
    ASN1_OBJECT *a, *b;
    int i;

    i = ca->type - cb->type;
    if (i)
        return i;
    a = ca->obj;
    b = cb->obj;
    switch (ca->type) {
    case ADDED_DATA:
        i = (a->length - b->length);
        if (i)
            return i;
        return memcmp(a->data, b->data, (size_t)a->length);
    case ADDED_SNAME:
        if (a->sn == NULL)
            return -1;
        else if (b->sn == NULL)
            return 1;
        else
            return strcmp(a->sn, b->sn);
    case ADDED_LNAME:
        if (a->ln == NULL)
            return -1;
        else if (b->ln == NULL)
            return 1;
        else
            return strcmp(a->ln, b->ln);
    case ADDED_NID:
        return a->nid - b->nid;
    default:
        /* abort(); */
        return 0;
    }
}