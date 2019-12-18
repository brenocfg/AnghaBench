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
struct kmsg_dumper {int dummy; } ;
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;

/* Variables and functions */
 int KMSG_DUMP_PANIC ; 
 int /*<<< orphan*/  opal_flush_console (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kmsg_dump_opal_console_flush(struct kmsg_dumper *dumper,
				     enum kmsg_dump_reason reason)
{
	/*
	 * Outside of a panic context the pollers will continue to run,
	 * so we don't need to do any special flushing.
	 */
	if (reason != KMSG_DUMP_PANIC)
		return;

	opal_flush_console(0);
}