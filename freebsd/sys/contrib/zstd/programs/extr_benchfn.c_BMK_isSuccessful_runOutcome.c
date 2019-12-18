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
struct TYPE_3__ {scalar_t__ error_tag_never_ever_use_directly; } ;
typedef  TYPE_1__ BMK_runOutcome_t ;

/* Variables and functions */

int BMK_isSuccessful_runOutcome(BMK_runOutcome_t outcome)
{
    return outcome.error_tag_never_ever_use_directly == 0;
}