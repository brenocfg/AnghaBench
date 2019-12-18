#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ext_nid; int /*<<< orphan*/  ext_flags; } ;
typedef  TYPE_1__ X509V3_EXT_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  X509V3_EXT_DYNAMIC ; 
 int X509V3_EXT_add (TYPE_1__*) ; 
 TYPE_1__* X509V3_EXT_get_nid (int) ; 
 int /*<<< orphan*/  X509V3_F_X509V3_EXT_ADD_ALIAS ; 
 int /*<<< orphan*/  X509V3_R_EXTENSION_NOT_FOUND ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509V3_EXT_add_alias(int nid_to, int nid_from)
{
    const X509V3_EXT_METHOD *ext;
    X509V3_EXT_METHOD *tmpext;

    if ((ext = X509V3_EXT_get_nid(nid_from)) == NULL) {
        X509V3err(X509V3_F_X509V3_EXT_ADD_ALIAS, X509V3_R_EXTENSION_NOT_FOUND);
        return 0;
    }
    if ((tmpext = OPENSSL_malloc(sizeof(*tmpext))) == NULL) {
        X509V3err(X509V3_F_X509V3_EXT_ADD_ALIAS, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    *tmpext = *ext;
    tmpext->ext_nid = nid_to;
    tmpext->ext_flags |= X509V3_EXT_DYNAMIC;
    return X509V3_EXT_add(tmpext);
}