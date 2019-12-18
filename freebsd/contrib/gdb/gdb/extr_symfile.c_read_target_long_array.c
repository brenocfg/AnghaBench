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
 int TARGET_LONG_BYTES ; 
 char* alloca (int) ; 
 unsigned int extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
read_target_long_array (CORE_ADDR memaddr, unsigned int *myaddr, int len)
{
  /* FIXME (alloca): Not safe if array is very large. */
  char *buf = alloca (len * TARGET_LONG_BYTES);
  int i;

  read_memory (memaddr, buf, len * TARGET_LONG_BYTES);
  for (i = 0; i < len; i++)
    myaddr[i] = extract_unsigned_integer (TARGET_LONG_BYTES * i + buf,
					  TARGET_LONG_BYTES);
}