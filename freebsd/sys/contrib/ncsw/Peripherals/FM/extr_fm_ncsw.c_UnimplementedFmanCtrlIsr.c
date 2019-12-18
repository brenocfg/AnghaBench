#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UnimplementedFmanCtrlIsr(t_Handle h_Arg, uint32_t event)
{
    UNUSED(h_Arg); UNUSED(event);

    REPORT_ERROR(MAJOR, E_NOT_SUPPORTED, ("Unimplemented FmCtl ISR!"));
}