#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct link {int nlayers; TYPE_1__** layer; } ;
struct cmdargs {int /*<<< orphan*/  prompt; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct link* command_ChooseLink (struct cmdargs const*) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,...) ; 

int
link_ShowLayers(struct cmdargs const *arg)
{
  struct link *l = command_ChooseLink(arg);
  int layer;

  for (layer = l->nlayers; layer; layer--)
    prompt_Printf(arg->prompt, "%s%s", layer == l->nlayers ? "" : ", ",
                  l->layer[layer - 1]->name);
  if (l->nlayers)
    prompt_Printf(arg->prompt, "\n");

  return 0;
}