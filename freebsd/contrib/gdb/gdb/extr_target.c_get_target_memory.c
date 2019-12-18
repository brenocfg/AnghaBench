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
struct target_ops {int dummy; } ;
typedef  scalar_t__ LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  TARGET_OBJECT_MEMORY ; 
 int /*<<< orphan*/  memory_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_read (struct target_ops*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__) ; 

void
get_target_memory (struct target_ops *ops, CORE_ADDR addr, void *buf,
		   LONGEST len)
{
  if (target_read (ops, TARGET_OBJECT_MEMORY, NULL, buf, addr, len)
      != len)
    memory_error (EIO, addr);
}