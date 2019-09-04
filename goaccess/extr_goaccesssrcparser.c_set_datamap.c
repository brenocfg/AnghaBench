#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ list_agents; scalar_t__ append_protocol; scalar_t__ append_method; } ;
struct TYPE_10__ {scalar_t__ uniq_nkey; int /*<<< orphan*/  data_nkey; int /*<<< orphan*/  root_nkey; int /*<<< orphan*/  root; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  agent_nkey; int /*<<< orphan*/  protocol; int /*<<< orphan*/  method; int /*<<< orphan*/  serve_time; int /*<<< orphan*/  resp_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* agent ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* protocol ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* method ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* maxts ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cumts ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* bw ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* visitor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hits ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rootmap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* datamap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ GParse ;
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_2__ GLogItem ;
typedef  TYPE_3__ GKeyData ;

/* Variables and functions */
 TYPE_7__ conf ; 
 int /*<<< orphan*/  insert_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_datamap (GLogItem * logitem, GKeyData * kdata, const GParse * parse)
{
  GModule module;
  module = parse->module;

  /* insert data */
  parse->datamap (kdata->data_nkey, kdata->data, module);

  /* insert rootmap and root-data map */
  if (parse->rootmap) {
    parse->rootmap (kdata->root_nkey, kdata->root, module);
    insert_root (kdata->data_nkey, kdata->root_nkey, module);
  }
  /* insert hits */
  if (parse->hits)
    parse->hits (kdata->data_nkey, module);
  /* insert visitors */
  if (parse->visitor && kdata->uniq_nkey != 0)
    parse->visitor (kdata->data_nkey, module);
  /* insert bandwidth */
  if (parse->bw)
    parse->bw (kdata->data_nkey, logitem->resp_size, module);
  /* insert averages time served */
  if (parse->cumts)
    parse->cumts (kdata->data_nkey, logitem->serve_time, module);
  /* insert averages time served */
  if (parse->maxts)
    parse->maxts (kdata->data_nkey, logitem->serve_time, module);
  /* insert method */
  if (parse->method && conf.append_method)
    parse->method (kdata->data_nkey, logitem->method, module);
  /* insert protocol */
  if (parse->protocol && conf.append_protocol)
    parse->protocol (kdata->data_nkey, logitem->protocol, module);
  /* insert agent */
  if (parse->agent && conf.list_agents)
    parse->agent (kdata->data_nkey, logitem->agent_nkey, module);
}