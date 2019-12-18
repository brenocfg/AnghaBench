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
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ psw_t ;

/* Variables and functions */
 int /*<<< orphan*/  __rewind_psw (TYPE_1__,unsigned long) ; 

__attribute__((used)) static void adjust_psw_addr(psw_t *psw, unsigned long len)
{
	psw->addr = __rewind_psw(*psw, -len);
}