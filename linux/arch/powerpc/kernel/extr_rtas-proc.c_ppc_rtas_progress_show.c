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
struct seq_file {int dummy; } ;

/* Variables and functions */
 scalar_t__* progress_led ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__*) ; 

__attribute__((used)) static int ppc_rtas_progress_show(struct seq_file *m, void *v)
{
	if (progress_led[0])
		seq_printf(m, "%s\n", progress_led);
	return 0;
}