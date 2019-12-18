#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  requiredActionFlag; scalar_t__ requiredAction; struct TYPE_4__* valid; } ;
typedef  TYPE_1__ t_FmPcdKgScheme ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void UpdateRequiredActionFlag(t_FmPcdKgScheme *p_Scheme, bool set)
{
    /* this routine is locked by the calling routine */
    ASSERT_COND(p_Scheme);
    ASSERT_COND(p_Scheme->valid);

    if (set)
        p_Scheme->requiredActionFlag = TRUE;
    else
    {
        p_Scheme->requiredAction = 0;
        p_Scheme->requiredActionFlag = FALSE;
    }
}