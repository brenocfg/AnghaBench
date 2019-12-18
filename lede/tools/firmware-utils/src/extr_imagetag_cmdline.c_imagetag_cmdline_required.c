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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  imagetag_cmdline_free (struct gengetopt_args_info*) ; 
 scalar_t__ imagetag_cmdline_required2 (struct gengetopt_args_info*,char const*,int /*<<< orphan*/ ) ; 

int
imagetag_cmdline_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  int result = EXIT_SUCCESS;

  if (imagetag_cmdline_required2(args_info, prog_name, 0) > 0)
    result = EXIT_FAILURE;

  if (result == EXIT_FAILURE)
    {
      imagetag_cmdline_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}