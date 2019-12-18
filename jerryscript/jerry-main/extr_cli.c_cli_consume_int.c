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
struct TYPE_3__ {char* error; scalar_t__ argc; int /*<<< orphan*/ ** argv; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_1__ cli_state_t ;

/* Variables and functions */
 long strtol (int /*<<< orphan*/ *,char**,int) ; 

int
cli_consume_int (cli_state_t *state_p) /**< state of the command line option processor */
{
  if (state_p->error != NULL)
  {
    return 0;
  }

  state_p->error = "Expected integer argument";

  if (state_p->argc <= 0)
  {
    state_p->arg = NULL;
    return 0;
  }

  state_p->arg = state_p->argv[0];

  char *endptr;
  long int value = strtol (state_p->arg, &endptr, 10);

  if (*endptr != '\0')
  {
    return 0;
  }

  state_p->error = NULL;
  state_p->argc--;
  state_p->argv++;
  return (int) value;
}