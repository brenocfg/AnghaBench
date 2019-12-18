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
struct TYPE_2__ {int modem_ready; } ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 TYPE_1__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
IFX_MEI_IsModemReady (DSL_DEV_Device_t * pDev)
{
	return DSL_DEV_PRIVATE(pDev)->modem_ready;
}