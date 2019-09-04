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
struct TYPE_2__ {int filenames_idx; scalar_t__ json_pretty_print; } ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  OVERALL_LOG ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  pclose_arr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  popen_arr_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poverall_log_path (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
poverall_log (GJSON * json, int sp)
{
  int idx, isp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  popen_arr_attr (json, OVERALL_LOG, sp);
  for (idx = 0; idx < conf.filenames_idx; ++idx)
    poverall_log_path (json, idx, isp);
  pclose_arr (json, sp, 1);
}