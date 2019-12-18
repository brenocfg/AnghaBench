#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* current_fiq ; 
 TYPE_1__ default_owner ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char*,int /*<<< orphan*/ ) ; 

int show_fiq_list(struct seq_file *p, int prec)
{
	if (current_fiq != &default_owner)
		seq_printf(p, "%*s:              %s\n", prec, "FIQ",
			current_fiq->name);

	return 0;
}