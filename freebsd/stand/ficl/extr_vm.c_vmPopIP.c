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
struct TYPE_3__ {int /*<<< orphan*/  rStack; scalar_t__ ip; } ;
typedef  scalar_t__ IPTYPE ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 

void vmPopIP(FICL_VM *pVM)
{
    pVM->ip = (IPTYPE)(stackPopPtr(pVM->rStack));
    return;
}