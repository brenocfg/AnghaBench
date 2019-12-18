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
struct TYPE_5__ {int /*<<< orphan*/ * (* create ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ CONF_METHOD ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_F_NCONF_NEW ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* NCONF_default () ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*) ; 

CONF *NCONF_new(CONF_METHOD *meth)
{
    CONF *ret;

    if (meth == NULL)
        meth = NCONF_default();

    ret = meth->create(meth);
    if (ret == NULL) {
        CONFerr(CONF_F_NCONF_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    return ret;
}