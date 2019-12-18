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
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_me ; 
 scalar_t__ highlighting ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
StopHighlight(void)
{
    (void) tputs(Str(T_me), 1, PUTPURE);
    highlighting = 0;
}