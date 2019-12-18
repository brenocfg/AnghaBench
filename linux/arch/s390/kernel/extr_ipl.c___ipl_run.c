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
 int /*<<< orphan*/  DIAG308_LOAD_CLEAR ; 
 int /*<<< orphan*/  __bpon () ; 
 int /*<<< orphan*/  diag308 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ipl_run(void *unused)
{
	__bpon();
	diag308(DIAG308_LOAD_CLEAR, NULL);
}