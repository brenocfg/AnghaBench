#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ max_hits; scalar_t__ max_visitors; } ;
struct TYPE_5__ {scalar_t__ hits; scalar_t__ visitors; } ;
typedef  TYPE_1__ GMetrics ;
typedef  TYPE_2__ GDashMeta ;

/* Variables and functions */

__attribute__((used)) static void
set_max_values (GDashMeta * meta, GMetrics * metrics)
{
  if (metrics->hits > meta->max_hits)
    meta->max_hits = metrics->hits;
  if (metrics->visitors > meta->max_visitors)
    meta->max_visitors = metrics->visitors;
}