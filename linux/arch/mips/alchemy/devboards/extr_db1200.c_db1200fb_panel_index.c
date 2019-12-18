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
 int /*<<< orphan*/  BCSR_SWITCHES ; 
 int bcsr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db1200fb_panel_index(void)
{
	return (bcsr_read(BCSR_SWITCHES) >> 8) & 0x0f;
}