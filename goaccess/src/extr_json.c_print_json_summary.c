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
typedef  int /*<<< orphan*/  GLog ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  int /*<<< orphan*/  GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  GENER_ID ; 
 TYPE_1__ conf ; 
 scalar_t__ num_panels () ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poverall_bandwidth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_datetime (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_excluded (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_files (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_invalid_reqs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_log (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_log_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_notfound (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_processed_time (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_refs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_requests (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_start_end_date (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_static_files (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_valid_reqs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poverall_visitors (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_json_summary (GJSON * json, GLog * glog, GHolder * holder)
{
  int sp = 0, isp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp = 1, isp = 2;

  popen_obj_attr (json, GENER_ID, sp);
  /* generated start/end date */
  poverall_start_end_date (json, holder, isp);
  /* generated date time */
  poverall_datetime (json, isp);
  /* total requests */
  poverall_requests (json, glog, isp);
  /* valid requests */
  poverall_valid_reqs (json, glog, isp);
  /* invalid requests */
  poverall_invalid_reqs (json, glog, isp);
  /* generated time */
  poverall_processed_time (json, isp);
  /* visitors */
  poverall_visitors (json, isp);
  /* files */
  poverall_files (json, isp);
  /* excluded hits */
  poverall_excluded (json, glog, isp);
  /* referrers */
  poverall_refs (json, isp);
  /* not found */
  poverall_notfound (json, isp);
  /* static files */
  poverall_static_files (json, isp);
  /* log size */
  poverall_log_size (json, isp);
  /* bandwidth */
  poverall_bandwidth (json, glog, isp);
  /* log path */
  poverall_log (json, isp);
  pclose_obj (json, sp, num_panels () > 0 ? 0 : 1);
}