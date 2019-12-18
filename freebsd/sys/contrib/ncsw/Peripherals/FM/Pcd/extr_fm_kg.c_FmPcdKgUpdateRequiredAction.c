#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  requiredAction; int /*<<< orphan*/  valid; } ;
typedef  TYPE_1__ t_FmPcdKgScheme ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 

void FmPcdKgUpdateRequiredAction(t_Handle h_Scheme, uint32_t requiredAction)
{
    t_FmPcdKgScheme *p_Scheme = (t_FmPcdKgScheme *)h_Scheme;

    /* this routine is protected by calling routine */

    ASSERT_COND(p_Scheme->valid);

    p_Scheme->requiredAction |= requiredAction;
}