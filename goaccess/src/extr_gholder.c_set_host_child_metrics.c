#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ GMetrics ;

/* Variables and functions */
 TYPE_1__* new_gmetrics () ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static int
set_host_child_metrics (char *data, uint8_t id, GMetrics ** nmetrics)
{
  GMetrics *metrics;

  metrics = new_gmetrics ();
  metrics->data = xstrdup (data);
  metrics->id = id;
  *nmetrics = metrics;

  return 0;
}