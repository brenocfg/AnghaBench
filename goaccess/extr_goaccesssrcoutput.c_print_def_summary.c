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
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fpopen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  print_def_overall_bandwidth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_excluded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_files (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_invalid_reqs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_log_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_notfound (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_processed_time (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_refs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_requests (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_static_files (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_valid_reqs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_def_overall_visitors (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_def_summary (FILE * fp, int sp)
{
  int isp = 0, iisp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1, iisp = sp + 2;

  /* open metrics block */
  fpopen_obj_attr (fp, "items", isp);

  print_def_overall_requests (fp, iisp);
  print_def_overall_valid_reqs (fp, iisp);
  print_def_overall_invalid_reqs (fp, iisp);
  print_def_overall_processed_time (fp, iisp);
  print_def_overall_visitors (fp, iisp);
  print_def_overall_files (fp, iisp);
  print_def_overall_excluded (fp, iisp);
  print_def_overall_refs (fp, iisp);
  print_def_overall_notfound (fp, iisp);
  print_def_overall_static_files (fp, iisp);
  print_def_overall_log_size (fp, iisp);
  print_def_overall_bandwidth (fp, iisp);

  /* close metrics block */
  fpclose_obj (fp, isp, 1);
}