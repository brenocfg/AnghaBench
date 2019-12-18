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
struct gengetopt_args_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_args (struct gengetopt_args_info*) ; 
 int /*<<< orphan*/  clear_given (struct gengetopt_args_info*) ; 
 int /*<<< orphan*/  init_args_info (struct gengetopt_args_info*) ; 

void
imagetag_cmdline_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);
}