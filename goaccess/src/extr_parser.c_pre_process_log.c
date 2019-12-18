#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int is_404; int is_static; int /*<<< orphan*/  resp_size; int /*<<< orphan*/  uniq_key; int /*<<< orphan*/  req; int /*<<< orphan*/ * agent; } ;
typedef  TYPE_1__ GLogItem ;
typedef  int /*<<< orphan*/  GLog ;

/* Variables and functions */
 int IGNORE_LEVEL_PANEL ; 
 int IGNORE_LEVEL_REQ ; 
 int /*<<< orphan*/ * alloc_string (char*) ; 
 int /*<<< orphan*/  count_invalid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  count_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_glog (TYPE_1__*) ; 
 int /*<<< orphan*/  get_uniq_visitor_key (TYPE_1__*) ; 
 int ignore_line (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  inc_resp_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* init_log_item (int /*<<< orphan*/ *) ; 
 scalar_t__ is_404 (TYPE_1__*) ; 
 scalar_t__ is_static (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_format (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  process_log (TYPE_1__*) ; 
 scalar_t__ valid_line (char*) ; 
 scalar_t__ verify_missing_fields (TYPE_1__*) ; 

__attribute__((used)) static int
pre_process_log (GLog * glog, char *line, int dry_run)
{
  GLogItem *logitem;
  int ret = 0;
  int ignorelevel = 0;

  /* soft ignore these lines */
  if (valid_line (line))
    return -1;

  count_process (glog);
  logitem = init_log_item (glog);
  /* Parse a line of log, and fill structure with appropriate values */
  if (parse_format (logitem, line) || verify_missing_fields (logitem)) {
    ret = 1;
    count_invalid (glog, line);
    goto cleanup;
  }

  /* agent will be null in cases where %u is not specified */
  if (logitem->agent == NULL)
    logitem->agent = alloc_string ("-");

  /* testing log only */
  if (dry_run)
    goto cleanup;

  ignorelevel = ignore_line (glog, logitem);
  /* ignore line */
  if (ignorelevel == IGNORE_LEVEL_PANEL)
    goto cleanup;

  if (is_404 (logitem))
    logitem->is_404 = 1;
  else if (is_static (logitem->req))
    logitem->is_static = 1;

  logitem->uniq_key = get_uniq_visitor_key (logitem);

  inc_resp_size (glog, logitem->resp_size);
  process_log (logitem);

  /* don't ignore line but neither count as valid */
  if (ignorelevel != IGNORE_LEVEL_REQ)
    count_valid (glog);

cleanup:
  free_glog (logitem);

  return ret;
}