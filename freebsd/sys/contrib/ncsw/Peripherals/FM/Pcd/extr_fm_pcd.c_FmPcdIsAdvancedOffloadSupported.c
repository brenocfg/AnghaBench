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
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int advancedOffloadSupport; } ;
typedef  TYPE_1__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 

bool FmPcdIsAdvancedOffloadSupported(t_Handle h_FmPcd)
{
    ASSERT_COND(h_FmPcd);
    return ((t_FmPcd*)h_FmPcd)->advancedOffloadSupport;
}