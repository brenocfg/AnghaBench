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

/* Variables and functions */
 int /*<<< orphan*/  read_option_args (int,char**) ; 
 int /*<<< orphan*/  set_default_static_files () ; 

__attribute__((used)) static void
parse_cmd_line (int argc, char **argv)
{
  read_option_args (argc, argv);
  set_default_static_files ();
}