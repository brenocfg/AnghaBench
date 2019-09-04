#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * metrics; } ;
typedef  size_t GModule ;
typedef  int /*<<< orphan*/  GKHashMetric ;

/* Variables and functions */
 int GSMTRC_TOTAL ; 
 int /*<<< orphan*/  free_metric_type (int /*<<< orphan*/ ) ; 
 TYPE_1__* gkh_storage ; 

__attribute__((used)) static void
free_metrics (GModule module)
{
  int i;
  GKHashMetric mtrc;

  for (i = 0; i < GSMTRC_TOTAL; i++) {
    mtrc = gkh_storage[module].metrics[i];
    free_metric_type (mtrc);
  }
}