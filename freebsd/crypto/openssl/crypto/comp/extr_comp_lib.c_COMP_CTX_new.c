#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* meth; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* init ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ COMP_METHOD ;
typedef  TYPE_2__ COMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_F_COMP_CTX_NEW ; 
 int /*<<< orphan*/  COMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

COMP_CTX *COMP_CTX_new(COMP_METHOD *meth)
{
    COMP_CTX *ret;

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        COMPerr(COMP_F_COMP_CTX_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->meth = meth;
    if ((ret->meth->init != NULL) && !ret->meth->init(ret)) {
        OPENSSL_free(ret);
        ret = NULL;
    }
    return ret;
}