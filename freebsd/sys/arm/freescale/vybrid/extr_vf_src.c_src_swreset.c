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
 int /*<<< orphan*/  SRC_SCR ; 
 int /*<<< orphan*/  SW_RST ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * src_sc ; 

int
src_swreset(void)
{

	if (src_sc == NULL)
		return (1);

	WRITE4(src_sc, SRC_SCR, SW_RST);

	return (0);
}