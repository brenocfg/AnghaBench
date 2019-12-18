#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ dump_log_pos ; 
 scalar_t__ dump_timestamp ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const,...) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ start_time ; 

inline int dump_line_header (const char *const tp, char ch) {
  if (start_time > now) { return -1; }
  if (dump_log_pos) { fprintf (out, "%lld\t",  log_cur_pos()); }
  if (dump_timestamp) { fprintf (out, "%d\t", now); }
  fprintf (out, "%s%c", tp, ch);
  return 0;
}