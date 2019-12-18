#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ h; } ;
struct TYPE_3__ {scalar_t__ filled; scalar_t__ h; } ;

/* Variables and functions */
 scalar_t__ R_cnt ; 
 scalar_t__ R_tot ; 
 scalar_t__ R_tot_groups ; 
 scalar_t__ R_tot_undef_hash ; 
 TYPE_2__ hm ; 
 TYPE_1__ hs ; 

__attribute__((used)) static void clear_res (void) {
  R_cnt = R_tot = R_tot_undef_hash = R_tot_groups = 0;
  hs.h = 0;
  hm.h = 0;
  hs.filled = 0;
}