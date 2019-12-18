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

char *
spr_cctrl_sel(unsigned sel0,unsigned sel1)
{
  unsigned sel=(sel1<<1) | sel0;
  char *ret="UNKNOWN";

  if      ( 0 == sel) {ret = "Reno";}
  else if ( 1 == sel) {ret = "Tahoe";}
  else if ( 2 == sel) {ret = "NewReno";}
  else if ( 3 == sel) {ret = "HighSpeed";}

  return ret;
}