#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* module; } ;
struct TYPE_11__ {size_t current; TYPE_1__* module; } ;
struct TYPE_10__ {TYPE_3__* metrics; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_4__* data; } ;
struct TYPE_7__ {int scroll; } ;
typedef  TYPE_4__ GDashData ;

/* Variables and functions */
 size_t HOSTS ; 
 TYPE_6__* dash ; 
 TYPE_5__ gscroll ; 
 int /*<<< orphan*/  invalid_ipaddr (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  load_agent_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_win ; 

__attribute__((used)) static void
load_ip_agent_list (void)
{
  int type_ip = 0;
  /* make sure we have a valid IP */
  int sel = gscroll.module[gscroll.current].scroll;
  GDashData item = dash->module[HOSTS].data[sel];

  if (!invalid_ipaddr (item.metrics->data, &type_ip))
    load_agent_list (main_win, item.metrics->data);
}