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
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int columns ; 
 int lines ; 

__attribute__((used)) static int
drv_getsize(TERMINAL_CONTROL_BLOCK * TCB, int *l, int *c)
{
    AssertTCB();
    assert(l != 0 && c != 0);
    *l = lines;
    *c = columns;
    return OK;
}