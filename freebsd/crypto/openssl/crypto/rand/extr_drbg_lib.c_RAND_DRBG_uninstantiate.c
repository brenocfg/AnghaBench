#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_1__* meth; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* uninstantiate ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  DRBG_ERROR ; 
 int RAND_DRBG_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_UNINSTANTIATE ; 
 int /*<<< orphan*/  RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int RAND_DRBG_uninstantiate(RAND_DRBG *drbg)
{
    if (drbg->meth == NULL) {
        drbg->state = DRBG_ERROR;
        RANDerr(RAND_F_RAND_DRBG_UNINSTANTIATE,
                RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED);
        return 0;
    }

    /* Clear the entire drbg->ctr struct, then reset some important
     * members of the drbg->ctr struct (e.g. keysize, df_ks) to their
     * initial values.
     */
    drbg->meth->uninstantiate(drbg);
    return RAND_DRBG_set(drbg, drbg->type, drbg->flags);
}