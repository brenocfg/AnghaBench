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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int log_cur_pos () ; 
 int now ; 
 int /*<<< orphan*/  stdout ; 

inline void dump_line_header (void) {
  if (dump_log_pos) { fprintf (stdout, "%lld\t",  log_cur_pos()); }
  if (dump_timestamp) { fprintf (stdout, "%d\t", now); }
}