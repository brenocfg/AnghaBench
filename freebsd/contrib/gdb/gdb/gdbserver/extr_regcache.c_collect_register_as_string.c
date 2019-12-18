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
 int /*<<< orphan*/  convert_int_to_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_data (int,int) ; 
 int /*<<< orphan*/  register_size (int) ; 

void
collect_register_as_string (int n, char *buf)
{
  convert_int_to_ascii (register_data (n, 1), buf, register_size (n));
}