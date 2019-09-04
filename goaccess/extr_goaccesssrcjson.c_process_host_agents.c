#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ json_pretty_print; } ;
struct TYPE_13__ {int size; TYPE_2__* items; } ;
struct TYPE_12__ {TYPE_1__* metrics; } ;
struct TYPE_11__ {int /*<<< orphan*/  agent; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_3__ GHolderItem ;
typedef  TYPE_4__ GAgents ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  TAB ; 
 TYPE_9__ conf ; 
 int /*<<< orphan*/  escape_json_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_agents_array (TYPE_4__*) ; 
 int /*<<< orphan*/  load_host_agents ; 
 TYPE_4__* new_gagents () ; 
 int nlines ; 
 int /*<<< orphan*/  pclose_arr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,...) ; 
 int set_host_agents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
process_host_agents (GJSON * json, GHolderItem * item, int iisp)
{
  GAgents *agents = new_gagents ();
  int i, n = 0, iiisp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    iiisp = iisp + 1;

  if (set_host_agents (item->metrics->data, load_host_agents, agents) == 1)
    return;

  pjson (json, ",%.*s%.*s\"items\": [%.*s", nlines, NL, iisp, TAB, nlines, NL);

  n = agents->size > 10 ? 10 : agents->size;
  for (i = 0; i < n; ++i) {
    pjson (json, "%.*s\"", iiisp, TAB);
    escape_json_output (json, agents->items[i].agent);
    if (i == n - 1)
      pjson (json, "\"");
    else
      pjson (json, "\",%.*s", nlines, NL);
  }

  pclose_arr (json, iisp, 1);

  /* clean stuff up */
  free_agents_array (agents);
}