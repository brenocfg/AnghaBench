#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_ascii_to_int (char*,char*,int) ; 
 int /*<<< orphan*/  current_inferior ; 
 TYPE_1__* get_regcache (int /*<<< orphan*/ ,int) ; 
 int register_bytes ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 

void
registers_from_string (char *buf)
{
  int len = strlen (buf);
  char *registers = get_regcache (current_inferior, 1)->registers;

  if (len != register_bytes * 2)
    {
      warning ("Wrong sized register packet (expected %d bytes, got %d)", 2*register_bytes, len);
      if (len > register_bytes * 2)
	len = register_bytes * 2;
    }
  convert_ascii_to_int (buf, registers, len / 2);
}