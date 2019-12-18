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
struct TYPE_2__ {int /*<<< orphan*/ * h_Pcd; } ;
typedef  TYPE_1__ t_Fm ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOT_FOUND ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void  FmUnregisterPcd(t_Handle h_Fm)
{
    t_Fm       *p_Fm = (t_Fm*)h_Fm;

    if (!p_Fm->h_Pcd)
        REPORT_ERROR(MAJOR, E_NOT_FOUND, ("PCD handle!"));

    p_Fm->h_Pcd = NULL;
}