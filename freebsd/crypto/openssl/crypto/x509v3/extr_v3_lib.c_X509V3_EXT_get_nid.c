#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ext_nid; } ;
typedef  TYPE_1__ X509V3_EXT_METHOD ;

/* Variables and functions */
 TYPE_1__** OBJ_bsearch_ext (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STANDARD_EXTENSION_COUNT ; 
 int /*<<< orphan*/  ext_list ; 
 int sk_X509V3_EXT_METHOD_find (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ const* sk_X509V3_EXT_METHOD_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standard_exts ; 

const X509V3_EXT_METHOD *X509V3_EXT_get_nid(int nid)
{
    X509V3_EXT_METHOD tmp;
    const X509V3_EXT_METHOD *t = &tmp, *const *ret;
    int idx;

    if (nid < 0)
        return NULL;
    tmp.ext_nid = nid;
    ret = OBJ_bsearch_ext(&t, standard_exts, STANDARD_EXTENSION_COUNT);
    if (ret)
        return *ret;
    if (!ext_list)
        return NULL;
    idx = sk_X509V3_EXT_METHOD_find(ext_list, &tmp);
    return sk_X509V3_EXT_METHOD_value(ext_list, idx);
}