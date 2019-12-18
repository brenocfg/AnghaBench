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
 int /*<<< orphan*/  IMX_USR2 ; 
 int IMX_USR2_RDR ; 
 int ub_getreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ub_tstc(void)
{

	return ((ub_getreg(IMX_USR2) & IMX_USR2_RDR) ? 1 : 0);
}