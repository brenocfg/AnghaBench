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
 int /*<<< orphan*/  AO ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  NET2ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ autoflush ; 
 int /*<<< orphan*/  doflush () ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xmitAO(void)
{
    NET2ADD(IAC, AO);
    printoption("SENT", IAC, AO);
    if (autoflush) {
	doflush();
    }
}