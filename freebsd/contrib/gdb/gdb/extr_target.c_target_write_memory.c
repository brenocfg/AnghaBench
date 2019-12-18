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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int target_xfer_memory (int /*<<< orphan*/ ,char*,int,int) ; 

int
target_write_memory (CORE_ADDR memaddr, char *myaddr, int len)
{
  return target_xfer_memory (memaddr, myaddr, len, 1);
}