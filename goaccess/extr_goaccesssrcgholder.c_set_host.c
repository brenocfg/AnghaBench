#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  idx; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* holder_callback ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  GRawDataItem ;
typedef  TYPE_1__ GPanel ;
typedef  TYPE_2__ GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  set_data_holder_metrics (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
set_host (GRawDataItem item, GHolder * h, const GPanel * panel, char *data,
          int hits)
{
  set_data_holder_metrics (item, h, xstrdup (data), hits);
  if (panel->holder_callback)
    panel->holder_callback (h);
  h->idx++;
}