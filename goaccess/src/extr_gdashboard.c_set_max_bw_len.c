#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* metrics; } ;
struct TYPE_9__ {int bw_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  sbw; } ;
struct TYPE_8__ {TYPE_1__ bw; } ;
typedef  TYPE_3__ GDashMeta ;
typedef  TYPE_4__ GDashData ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_BW_LBL ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_max_bw_len (GDashMeta * meta, GDashData * idata)
{
  int vlen = strlen (idata->metrics->bw.sbw);
  int llen = strlen (MTRC_BW_LBL);

  if (vlen > meta->bw_len)
    meta->bw_len = vlen;

  /* if outputting with column names, then determine if the value is
   * longer than the length of the column name */
  if (llen > meta->bw_len)
    meta->bw_len = llen;
}