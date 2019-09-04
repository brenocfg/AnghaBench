#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ json_pretty_print; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ GHTML ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_6__ conf ; 
 int /*<<< orphan*/  fpskeyival (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpskeysval (int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ ) ; 
 char* module_to_desc (int /*<<< orphan*/ ) ; 
 char* module_to_head (int /*<<< orphan*/ ) ; 
 char* module_to_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_def_meta (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int /*<<< orphan*/  print_def_metrics (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  print_def_plot (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  print_def_sort (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 

__attribute__((used)) static void
print_panel_def_meta (FILE * fp, const GHTML * def, int sp)
{
  const char *desc = module_to_desc (def->module);
  const char *head = module_to_head (def->module);
  const char *id = module_to_id (def->module);

  int isp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  print_def_meta (fp, head, desc, sp);

  fpskeysval (fp, "id", id, isp, 0);
  fpskeyival (fp, "table", def->table, isp, 0);

  print_def_sort (fp, def, isp);
  print_def_plot (fp, def, isp);
  print_def_metrics (fp, def, isp);
}