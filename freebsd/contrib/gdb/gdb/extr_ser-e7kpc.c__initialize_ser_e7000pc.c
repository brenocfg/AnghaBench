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
 int /*<<< orphan*/  e7000pc_ops ; 
 int /*<<< orphan*/  serial_add_interface (int /*<<< orphan*/ *) ; 

void
_initialize_ser_e7000pc (void)
{
#if defined __GO32__ || defined _WIN32
  serial_add_interface (&e7000pc_ops);
#endif  
}