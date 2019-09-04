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
struct TYPE_2__ {scalar_t__ json_pretty_print; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GENER_ID ; 
 int /*<<< orphan*/  T_HEAD ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpopen_obj_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_def_meta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_def_summary (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_json_def_summary (FILE * fp)
{
  int sp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp = 1;

  /* output open panel attribute */
  fpopen_obj_attr (fp, GENER_ID, sp);
  print_def_meta (fp, _(T_HEAD), "", sp);
  print_def_summary (fp, sp);
  /* output close panel attribute */
  fpclose_obj (fp, sp, 0);
}