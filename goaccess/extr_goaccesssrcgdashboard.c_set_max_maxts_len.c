#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  serve_usecs; } ;
struct TYPE_11__ {TYPE_1__* metrics; } ;
struct TYPE_10__ {int maxts_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  sts; } ;
struct TYPE_8__ {TYPE_2__ maxts; } ;
typedef  TYPE_3__ GDashMeta ;
typedef  TYPE_4__ GDashData ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_AVGTS_LBL ; 
 TYPE_7__ conf ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_max_maxts_len (GDashMeta * meta, GDashData * idata)
{
  int vlen = 0, llen = 0;

  if (!conf.serve_usecs || !idata->metrics->maxts.sts)
    return;

  vlen = strlen (idata->metrics->maxts.sts);
  llen = strlen (MTRC_AVGTS_LBL);

  if (vlen > meta->maxts_len)
    meta->maxts_len = vlen;

  /* if outputting with column names, then determine if the value is
   * longer than the length of the column name */
  if (llen > meta->maxts_len)
    meta->maxts_len = llen;
}