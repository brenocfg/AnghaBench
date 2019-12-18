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
 int /*<<< orphan*/  convert_int_to_ascii (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_inferior ; 
 TYPE_1__* get_regcache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_bytes ; 

void
registers_to_string (char *buf)
{
  char *registers = get_regcache (current_inferior, 1)->registers;

  convert_int_to_ascii (registers, buf, register_bytes);
}