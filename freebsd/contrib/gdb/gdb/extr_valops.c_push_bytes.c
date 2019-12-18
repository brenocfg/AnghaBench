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
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ INNER_THAN (int,int) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 

CORE_ADDR
push_bytes (CORE_ADDR sp, char *buffer, int len)
{
  if (INNER_THAN (1, 2))
    {
      /* stack grows downward */
      sp -= len;
      write_memory (sp, buffer, len);
    }
  else
    {
      /* stack grows upward */
      write_memory (sp, buffer, len);
      sp += len;
    }

  return sp;
}