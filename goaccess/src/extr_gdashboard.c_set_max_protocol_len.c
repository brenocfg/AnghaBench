#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  append_protocol; } ;
struct TYPE_9__ {TYPE_1__* metrics; } ;
struct TYPE_8__ {int protocol_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  protocol; } ;
typedef  TYPE_2__ GDashMeta ;
typedef  TYPE_3__ GDashData ;

/* Variables and functions */
 int /*<<< orphan*/  MTRC_PROTOCOLS_SHORT_LBL ; 
 TYPE_6__ conf ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_max_protocol_len (GDashMeta * meta, GDashData * idata)
{
  int vlen = 0, llen = 0;

  if (!conf.append_protocol || !idata->metrics->protocol)
    return;

  vlen = strlen (idata->metrics->protocol);
  llen = strlen (MTRC_PROTOCOLS_SHORT_LBL);

  if (vlen > meta->protocol_len)
    meta->protocol_len = vlen;

  /* if outputting with column names, then determine if the value is
   * longer than the length of the column name */
  if (llen > meta->protocol_len)
    meta->protocol_len = llen;
}