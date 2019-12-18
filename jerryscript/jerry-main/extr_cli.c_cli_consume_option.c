#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* error; scalar_t__ argc; char const* arg; char** argv; TYPE_2__* opts; } ;
typedef  TYPE_1__ cli_state_t ;
struct TYPE_5__ {int id; int /*<<< orphan*/ * opt; int /*<<< orphan*/ * longopt; } ;
typedef  TYPE_2__ cli_opt_t ;

/* Variables and functions */
 int CLI_OPT_DEFAULT ; 
 int CLI_OPT_END ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
cli_consume_option (cli_state_t *state_p) /**< state of the command line option processor */
{
  if (state_p->error != NULL)
  {
    return CLI_OPT_END;
  }

  if (state_p->argc <= 0)
  {
    state_p->arg = NULL;
    return CLI_OPT_END;
  }

  const char *arg = state_p->argv[0];

  state_p->arg = arg;

  if (arg[0] != '-')
  {
    return CLI_OPT_DEFAULT;
  }

  if (arg[1] == '-')
  {
    arg += 2;

    for (const cli_opt_t *opt = state_p->opts; opt->id != CLI_OPT_DEFAULT; opt++)
    {
      if (opt->longopt != NULL && strcmp (arg, opt->longopt) == 0)
      {
        state_p->argc--;
        state_p->argv++;
        return opt->id;
      }
    }

    state_p->error = "Unknown long option";
    return CLI_OPT_END;
  }

  arg++;

  for (const cli_opt_t *opt = state_p->opts; opt->id != CLI_OPT_DEFAULT; opt++)
  {
    if (opt->opt != NULL && strcmp (arg, opt->opt) == 0)
    {
      state_p->argc--;
      state_p->argv++;
      return opt->id;
    }
  }

  state_p->error = "Unknown option";
  return CLI_OPT_END;
}