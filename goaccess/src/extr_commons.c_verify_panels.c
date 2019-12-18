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
struct TYPE_2__ {int ignore_panel_idx; int /*<<< orphan*/  ignore_panels; int /*<<< orphan*/  log_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  REMOTE_USER ; 
 int TOTAL_MODULES ; 
 int /*<<< orphan*/  VIRTUAL_HOSTS ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  remove_module (int /*<<< orphan*/ ) ; 
 scalar_t__ str_inarray (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

void
verify_panels (void)
{
  int ignore_panel_idx = conf.ignore_panel_idx;

  /* Remove virtual host panel if no '%v' within log format */
  if (!conf.log_format)
    return;

  if (!strstr (conf.log_format, "%v") && ignore_panel_idx < TOTAL_MODULES) {
    if (str_inarray ("VIRTUAL_HOSTS", conf.ignore_panels, ignore_panel_idx) < 0)
      remove_module (VIRTUAL_HOSTS);
  }
  if (!strstr (conf.log_format, "%e") && ignore_panel_idx < TOTAL_MODULES) {
    if (str_inarray ("REMOTE_USER", conf.ignore_panels, ignore_panel_idx) < 0)
      remove_module (REMOTE_USER);
  }
}