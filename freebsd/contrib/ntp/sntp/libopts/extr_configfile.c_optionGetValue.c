#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* nestVal; } ;
struct TYPE_7__ {scalar_t__ valType; int /*<<< orphan*/  pzName; TYPE_1__ v; } ;
typedef  TYPE_2__ tOptionValue ;
struct TYPE_8__ {int useCt; int /*<<< orphan*/  apzArgs; } ;
typedef  TYPE_3__ tArgList ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ OPARG_TYPE_HIERARCHY ; 
 void** VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

tOptionValue const *
optionGetValue(tOptionValue const * oov, char const * vname)
{
    tArgList *           arg_list;
    const tOptionValue * res = NULL;

    if ((oov == NULL) || (oov->valType != OPARG_TYPE_HIERARCHY)) {
        errno = EINVAL;
        return res;
    }
    arg_list = oov->v.nestVal;

    if (arg_list->useCt > 0) {
        int           ct     = arg_list->useCt;
        const void ** ovlist = VOIDP(arg_list->apzArgs);

        if (vname == NULL) {
            res = (const tOptionValue *)*ovlist;

        } else do {
            const tOptionValue * opt_val = *(ovlist++);
            if (strcmp(opt_val->pzName, vname) == 0) {
                res = opt_val;
                break;
            }
        } while (--ct > 0);
    }
    if (res == NULL)
        errno = ENOENT;
    return res;
}