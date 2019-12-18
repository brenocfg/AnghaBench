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
struct TYPE_6__ {long flags; TYPE_1__* meth; } ;
struct TYPE_5__ {long (* dso_ctrl ) (TYPE_2__*,int,long,void*) ;} ;
typedef  TYPE_2__ DSO ;

/* Variables and functions */
#define  DSO_CTRL_GET_FLAGS 130 
#define  DSO_CTRL_OR_FLAGS 129 
#define  DSO_CTRL_SET_FLAGS 128 
 int /*<<< orphan*/  DSO_F_DSO_CTRL ; 
 int /*<<< orphan*/  DSO_R_UNSUPPORTED ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 long stub1 (TYPE_2__*,int,long,void*) ; 

long DSO_ctrl(DSO *dso, int cmd, long larg, void *parg)
{
    if (dso == NULL) {
        DSOerr(DSO_F_DSO_CTRL, ERR_R_PASSED_NULL_PARAMETER);
        return -1;
    }
    /*
     * We should intercept certain generic commands and only pass control to
     * the method-specific ctrl() function if it's something we don't handle.
     */
    switch (cmd) {
    case DSO_CTRL_GET_FLAGS:
        return dso->flags;
    case DSO_CTRL_SET_FLAGS:
        dso->flags = (int)larg;
        return 0;
    case DSO_CTRL_OR_FLAGS:
        dso->flags |= (int)larg;
        return 0;
    default:
        break;
    }
    if ((dso->meth == NULL) || (dso->meth->dso_ctrl == NULL)) {
        DSOerr(DSO_F_DSO_CTRL, DSO_R_UNSUPPORTED);
        return -1;
    }
    return dso->meth->dso_ctrl(dso, cmd, larg, parg);
}