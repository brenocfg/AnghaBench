#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ serve_usecs; } ;
struct TYPE_12__ {TYPE_7__* sts; } ;
struct TYPE_11__ {TYPE_7__* sts; } ;
struct TYPE_10__ {TYPE_7__* sts; } ;
struct TYPE_9__ {TYPE_7__* sbw; } ;
struct TYPE_14__ {TYPE_4__ maxts; TYPE_3__ cumts; TYPE_2__ avgts; TYPE_1__ bw; struct TYPE_14__* data; } ;
struct TYPE_13__ {TYPE_7__* metrics; } ;
typedef  TYPE_5__ GDashData ;

/* Variables and functions */
 TYPE_8__ conf ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 

__attribute__((used)) static void
free_dashboard_data (GDashData item)
{
  if (item.metrics == NULL)
    return;

  if (item.metrics->data)
    free (item.metrics->data);
  if (item.metrics->bw.sbw)
    free (item.metrics->bw.sbw);
  if (conf.serve_usecs && item.metrics->avgts.sts)
    free (item.metrics->avgts.sts);
  if (conf.serve_usecs && item.metrics->cumts.sts)
    free (item.metrics->cumts.sts);
  if (conf.serve_usecs && item.metrics->maxts.sts)
    free (item.metrics->maxts.sts);
  free (item.metrics);
}