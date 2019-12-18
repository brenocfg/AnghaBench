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
typedef  int /*<<< orphan*/  tOptionValue ;
struct TYPE_4__ {TYPE_2__* optCookie; int /*<<< orphan*/  fOptState; } ;
typedef  TYPE_1__ tOptDesc ;
struct TYPE_5__ {int useCt; int /*<<< orphan*/  apzArgs; } ;
typedef  TYPE_2__ tArgList ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ OPARG_TYPE_HIERARCHY ; 
 scalar_t__ OPTST_GET_ARGTYPE (int /*<<< orphan*/ ) ; 
 void** VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

tOptionValue const *
optionFindNextValue(const tOptDesc * odesc, const tOptionValue * pPrevVal,
                    char const * pzName, char const * pzVal)
{
    bool old_found = false;
    const tOptionValue * res = NULL;

    (void)pzName;
    (void)pzVal;

    if (  (odesc == NULL)
       || (OPTST_GET_ARGTYPE(odesc->fOptState) != OPARG_TYPE_HIERARCHY))  {
        errno = EINVAL;
    }

    else if (odesc->optCookie == NULL) {
        errno = ENOENT;
    }

    else do {
        tArgList *    argl  = odesc->optCookie;
        int           ct    = argl->useCt;
        const void ** poptv = VOIDP(argl->apzArgs);

        while (--ct >= 0) {
            const tOptionValue * pOV = *(poptv++);
            if (old_found) {
                res = pOV;
                break;
            }
            if (pOV == pPrevVal)
                old_found = true;
        }
        if (res == NULL)
            errno = ENOENT;
    } while (false);

    return res;
}