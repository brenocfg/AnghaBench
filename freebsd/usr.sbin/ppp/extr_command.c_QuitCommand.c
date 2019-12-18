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
struct cmdargs {size_t argc; size_t argn; TYPE_1__* prompt; int /*<<< orphan*/ * argv; } ;
struct TYPE_3__ {int auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cleanup () ; 
 int LOCAL_AUTH ; 
 int /*<<< orphan*/  prompt_Destroy (TYPE_1__*,int) ; 
 scalar_t__ prompt_IsController (TYPE_1__*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
QuitCommand(struct cmdargs const *arg)
{
  if (!arg->prompt || prompt_IsController(arg->prompt) ||
      (arg->argc > arg->argn && !strcasecmp(arg->argv[arg->argn], "all") &&
       (arg->prompt->auth & LOCAL_AUTH)))
    Cleanup();
  if (arg->prompt)
    prompt_Destroy(arg->prompt, 1);

  return 0;
}