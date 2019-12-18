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
struct child_process {int dummy; } ;
struct subprocess_entry {struct child_process process; } ;

/* Variables and functions */

__attribute__((used)) static inline struct child_process *subprocess_get_child_process(
		struct subprocess_entry *entry)
{
	return &entry->process;
}