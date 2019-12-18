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

/* Variables and functions */
 int FICL_DEFAULT_STACK ; 
 int defaultStack ; 

int ficlSetStackSize(int nStackCells)
{
    if (nStackCells >= FICL_DEFAULT_STACK)
        defaultStack = nStackCells;
    else
        defaultStack = FICL_DEFAULT_STACK;

    return defaultStack;
}