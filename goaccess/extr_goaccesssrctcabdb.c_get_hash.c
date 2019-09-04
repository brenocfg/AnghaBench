#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* metrics; } ;
struct TYPE_3__ {scalar_t__ metric; void* store; } ;
typedef  TYPE_1__ GTCStorageMetric ;
typedef  scalar_t__ GSMetric ;
typedef  size_t GModule ;

/* Variables and functions */
 int GSMTRC_TOTAL ; 
 TYPE_2__* tc_storage ; 

__attribute__((used)) static void *
get_hash (GModule module, GSMetric metric)
{
  void *hash = NULL;
  int i;
  GTCStorageMetric mtrc;

  if (!tc_storage)
    return NULL;

  for (i = 0; i < GSMTRC_TOTAL; i++) {
    mtrc = tc_storage[module].metrics[i];
    if (mtrc.metric != metric)
      continue;
    hash = mtrc.store;
    break;
  }

  return hash;
}