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
 int /*<<< orphan*/  collect_register_as_string (int,char*) ; 
 int register_size (int) ; 
 void* tohex (int) ; 

__attribute__((used)) static char *
outreg (int regno, char *buf)
{
  if ((regno >> 12) != 0)
    *buf++ = tohex ((regno >> 12) & 0xf);
  if ((regno >> 8) != 0)
    *buf++ = tohex ((regno >> 8) & 0xf);
  *buf++ = tohex ((regno >> 4) & 0xf);
  *buf++ = tohex (regno & 0xf);
  *buf++ = ':';
  collect_register_as_string (regno, buf);
  buf += 2 * register_size (regno);
  *buf++ = ';';

  return buf;
}