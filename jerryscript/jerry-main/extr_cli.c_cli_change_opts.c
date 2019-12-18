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
struct TYPE_3__ {int /*<<< orphan*/  const* opts; } ;
typedef  TYPE_1__ cli_state_t ;
typedef  int /*<<< orphan*/  cli_opt_t ;

/* Variables and functions */

void
cli_change_opts (cli_state_t *state_p, /**< state of the command line option processor */
                 const cli_opt_t *options_p) /**< array of option definitions, terminated by CLI_OPT_DEFAULT */
{
  state_p->opts = options_p;
}