#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long mask; int flags; int /*<<< orphan*/  maxsize; int /*<<< orphan*/  minsize; } ;
typedef  TYPE_1__ ASN1_STRING_TABLE ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 TYPE_1__* ASN1_STRING_TABLE_get (int) ; 
 int ASN1_mbstring_copy (int /*<<< orphan*/ **,unsigned char const*,int,int,unsigned long) ; 
 int ASN1_mbstring_ncopy (int /*<<< orphan*/ **,unsigned char const*,int,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long DIRSTRING_TYPE ; 
 int STABLE_NO_MASK ; 
 unsigned long global_mask ; 

ASN1_STRING *ASN1_STRING_set_by_NID(ASN1_STRING **out,
                                    const unsigned char *in, int inlen,
                                    int inform, int nid)
{
    ASN1_STRING_TABLE *tbl;
    ASN1_STRING *str = NULL;
    unsigned long mask;
    int ret;

    if (out == NULL)
        out = &str;
    tbl = ASN1_STRING_TABLE_get(nid);
    if (tbl != NULL) {
        mask = tbl->mask;
        if (!(tbl->flags & STABLE_NO_MASK))
            mask &= global_mask;
        ret = ASN1_mbstring_ncopy(out, in, inlen, inform, mask,
                                  tbl->minsize, tbl->maxsize);
    } else {
        ret = ASN1_mbstring_copy(out, in, inlen, inform,
                                 DIRSTRING_TYPE & global_mask);
    }
    if (ret <= 0)
        return NULL;
    return *out;
}