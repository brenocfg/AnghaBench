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
struct diff_options {scalar_t__ output_prefix; } ;

/* Variables and functions */
 struct diff_options* default_diffopt ; 
 scalar_t__ diff_output_prefix_callback ; 

void graph_setup_line_prefix(struct diff_options *diffopt)
{
	default_diffopt = diffopt;

	/* setup an output prefix callback if necessary */
	if (diffopt && !diffopt->output_prefix)
		diffopt->output_prefix = diff_output_prefix_callback;
}