#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_opt_subcommand_desc2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int optch; char* name; } ;
typedef  TYPE_1__ apr_getopt_option_t ;

/* Variables and functions */
 TYPE_1__* svn_opt_get_option_from_code2 (int,TYPE_1__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const apr_getopt_option_t *
get_option_from_code(const char **long_alias,
                     int code,
                     const apr_getopt_option_t *option_table,
                     const svn_opt_subcommand_desc2_t *command,
                     apr_pool_t *pool)
{
  const apr_getopt_option_t *i;
  const apr_getopt_option_t *opt
    = svn_opt_get_option_from_code2(code, option_table, command, pool);

  /* Find a long alias in the table, if there is one. */
  *long_alias = NULL;
  for (i = option_table; i->optch; i++)
    {
      if (i->optch == code && i->name != opt->name)
        {
          *long_alias = i->name;
          break;
        }
    }

  return opt;
}