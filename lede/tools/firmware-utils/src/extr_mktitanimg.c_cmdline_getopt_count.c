#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* opt_args; } ;
struct TYPE_3__ {int optc; } ;

/* Variables and functions */
 TYPE_2__ cmdline_data ; 

int cmdline_getopt_count(char opt)
{
	int				index;

	/* Calculate index value */
	index = opt - 'a';
	if(index < 0 || index > 25) return -1;

	/* Return number of arguments for this option */
	return(cmdline_data.opt_args[index].optc);
}