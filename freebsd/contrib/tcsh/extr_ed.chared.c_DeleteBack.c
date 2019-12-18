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
 int /*<<< orphan*/ * Cursor ; 
 int /*<<< orphan*/ * InputBuf ; 
 int /*<<< orphan*/  c_delbefore (int) ; 

void
DeleteBack(int n)		/* delete the n characters before . */
{
    if (n <= 0)
	return;
    if (Cursor >= &InputBuf[n]) {
	c_delbefore(n);		/* delete before dot */
    }
}