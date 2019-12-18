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
 int target_xfer_memory_partial (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int*) ; 

int
target_read_memory_partial (CORE_ADDR memaddr, char *buf, int len, int *err)
{
  return target_xfer_memory_partial (memaddr, buf, len, 0, err);
}