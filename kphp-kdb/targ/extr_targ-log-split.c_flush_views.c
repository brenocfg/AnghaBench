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
struct lev_targ_views {unsigned int ad_id; scalar_t__ views; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_VIEWS ; 
 unsigned int MAX_AD_ID ; 
 scalar_t__* Views ; 
 int wr_bytes ; 
 int /*<<< orphan*/  wr_rec ; 
 int /*<<< orphan*/  wr_views_rec ; 
 struct lev_targ_views* write_alloc (int) ; 

__attribute__((used)) static void flush_views (unsigned ad_id) {
  if (ad_id >= MAX_AD_ID || !Views[ad_id]) {
    return;
  }
  struct lev_targ_views *E = write_alloc (12);
  E->type = LEV_TARG_VIEWS;
  E->ad_id = ad_id;
  E->views = Views[ad_id];
  Views[ad_id] = 0;
  wr_views_rec++;
  wr_rec++;
  wr_bytes += 12;
}