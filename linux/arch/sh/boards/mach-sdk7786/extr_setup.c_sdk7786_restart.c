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
 int /*<<< orphan*/  SRSTR ; 
 int /*<<< orphan*/  fpga_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdk7786_restart(char *cmd)
{
	fpga_write_reg(0xa5a5, SRSTR);
}