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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  references; } ;
typedef  TYPE_1__ DSO ;

/* Variables and functions */
 scalar_t__ CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_F_DSO_UP_REF ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r ; 

int DSO_up_ref(DSO *dso)
{
    int i;

    if (dso == NULL) {
        DSOerr(DSO_F_DSO_UP_REF, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (CRYPTO_UP_REF(&dso->references, &i, dso->lock) <= 0)
        return 0;

    REF_PRINT_COUNT("DSO", r);
    REF_ASSERT_ISNT(i < 2);
    return ((i > 1) ? 1 : 0);
}