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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_char ;
struct TYPE_3__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPopUNS (int /*<<< orphan*/ ) ; 

void
ficlOutb(FICL_VM *pVM)
{
	u_char c;
	uint32_t port;

	port=stackPopUNS(pVM->pStack);
	c=(u_char)stackPopINT(pVM->pStack);
	outb(port,c);
}