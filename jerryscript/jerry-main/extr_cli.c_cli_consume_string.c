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
struct TYPE_3__ {char* error; scalar_t__ argc; char const* arg; char const** argv; } ;
typedef  TYPE_1__ cli_state_t ;

/* Variables and functions */

const char *
cli_consume_string (cli_state_t *state_p) /**< state of the command line option processor */
{
  if (state_p->error != NULL)
  {
    return NULL;
  }

  if (state_p->argc <= 0)
  {
    state_p->error = "Expected string argument";
    state_p->arg = NULL;
    return NULL;
  }

  state_p->arg = state_p->argv[0];

  state_p->argc--;
  state_p->argv++;
  return state_p->arg;
}