#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct GPanel_ {int dummy; } ;
struct TYPE_7__ {scalar_t__ json_pretty_print; } ;
struct TYPE_6__ {int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  GPercTotals ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 TYPE_5__ conf ; 
 int /*<<< orphan*/  module_to_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_data_metrics (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,struct GPanel_ const*) ; 
 int /*<<< orphan*/  print_meta_data (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
print_json_data (GJSON * json, GHolder * h, GPercTotals totals,
                 const struct GPanel_ *panel)
{
  int sp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp = 1;

  /* output open panel attribute */
  popen_obj_attr (json, module_to_id (h->module), sp);
  /* output panel metadata */
  print_meta_data (json, h, sp);
  /* output panel data */
  print_data_metrics (json, h, totals, sp, panel);
  /* output close panel attribute */
  pclose_obj (json, sp, 1);
}