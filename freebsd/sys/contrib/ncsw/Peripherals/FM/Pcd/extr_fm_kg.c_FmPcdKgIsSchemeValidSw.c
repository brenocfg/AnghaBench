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
struct TYPE_2__ {int valid; } ;
typedef  TYPE_1__ t_FmPcdKgScheme ;

/* Variables and functions */

bool FmPcdKgIsSchemeValidSw(t_Handle h_Scheme)
{
    t_FmPcdKgScheme     *p_Scheme = (t_FmPcdKgScheme*)h_Scheme;

    return p_Scheme->valid;
}