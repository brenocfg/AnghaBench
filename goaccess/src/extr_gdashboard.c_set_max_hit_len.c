#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* metrics; } ;
struct TYPE_7__ {int hits_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  hits; } ;
typedef  TYPE_2__ GDashMeta ;
typedef  TYPE_3__ GDashData ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_HITS_LBL ; 
 int intlen (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_max_hit_len (GDashMeta * meta, GDashData * idata)
{
  int vlen = intlen (idata->metrics->hits);
  int llen = strlen (MTRC_HITS_LBL);

  if (vlen > meta->hits_len)
    meta->hits_len = vlen;

  /* if outputting with column names, then determine if the value is
   * longer than the length of the column name */
  if (llen > meta->hits_len)
    meta->hits_len = llen;
}