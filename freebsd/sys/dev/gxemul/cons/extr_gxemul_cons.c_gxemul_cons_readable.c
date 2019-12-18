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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GC_LOCK_ASSERT () ; 
 scalar_t__ buffer_data ; 
 int buffer_valid ; 
 scalar_t__ gxemul_cons_data_read () ; 

__attribute__((used)) static int
gxemul_cons_readable(void)
{
	uint32_t v;

	GC_LOCK_ASSERT();

	if (buffer_valid)
		return (1);
	v = gxemul_cons_data_read();
	if (v != 0) {
		buffer_valid = 1;
		buffer_data = v;
		return (1);
	}
	return (0);
}