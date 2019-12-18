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
typedef  int /*<<< orphan*/  GDashMeta ;
typedef  int /*<<< orphan*/  GDashData ;

/* Variables and functions */
 int /*<<< orphan*/  set_max_avgts_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_bw_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_cumts_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_data_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_hit_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_hit_perc_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_maxts_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_method_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_protocol_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_visitors_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_max_visitors_perc_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_metrics_len (GDashMeta * meta, GDashData * idata)
{
  /* integer-based length */
  set_max_hit_len (meta, idata);
  set_max_hit_perc_len (meta, idata);
  set_max_visitors_len (meta, idata);
  set_max_visitors_perc_len (meta, idata);

  /* string-based length */
  set_max_bw_len (meta, idata);
  set_max_avgts_len (meta, idata);
  set_max_cumts_len (meta, idata);
  set_max_maxts_len (meta, idata);

  set_max_method_len (meta, idata);
  set_max_protocol_len (meta, idata);
  set_max_data_len (meta, idata);
}