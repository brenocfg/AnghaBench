#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ json_pretty_print; } ;
struct TYPE_5__ {int module; } ;
typedef  TYPE_1__ GHTML ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int TOTAL_MODULES ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fpjson (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpopen_obj_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_to_id (int) ; 
 int /*<<< orphan*/  nlines ; 
 int /*<<< orphan*/  print_panel_def_meta (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 

__attribute__((used)) static void
print_json_def (FILE * fp, const GHTML * def)
{
  int sp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp = 1;

  /* output open panel attribute */
  fpopen_obj_attr (fp, module_to_id (def->module), sp);
  /* output panel data definitions */
  print_panel_def_meta (fp, def, sp);
  /* output close panel attribute */
  fpclose_obj (fp, sp, 1);

  fpjson (fp, (def->module != TOTAL_MODULES - 1) ? ",%.*s" : "%.*s", nlines,
          NL);
}