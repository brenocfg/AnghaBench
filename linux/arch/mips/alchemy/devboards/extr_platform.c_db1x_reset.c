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
 int /*<<< orphan*/  BCSR_RESETS ; 
 int /*<<< orphan*/  BCSR_SYSTEM ; 
 int /*<<< orphan*/  bcsr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db1x_reset(char *c)
{
	bcsr_write(BCSR_RESETS, 0);
	bcsr_write(BCSR_SYSTEM, 0);
}