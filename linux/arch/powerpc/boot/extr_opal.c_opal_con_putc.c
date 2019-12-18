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
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int be64_to_cpu (int) ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  opal_con_id ; 
 int /*<<< orphan*/  opal_console_write (int /*<<< orphan*/ ,int*,unsigned char*) ; 
 scalar_t__ opal_console_write_buffer_space (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opal_poll_events (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opal_con_putc(unsigned char c)
{
	int64_t rc;
	uint64_t olen, len;

	do {
		rc = opal_console_write_buffer_space(opal_con_id, &olen);
		len = be64_to_cpu(olen);
		if (rc)
			return;
		opal_poll_events(NULL);
	} while (len < 1);


	olen = cpu_to_be64(1);
	opal_console_write(opal_con_id, &olen, &c);
}