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
struct TYPE_3__ {scalar_t__ metric; int type; void* su64; void* igsl; void* ss32; void* si32; void* iu64; void* is32; void* ii32; } ;
typedef  scalar_t__ GSMetric ;
typedef  size_t GModule ;
typedef  TYPE_1__ GKHashMetric ;

/* Variables and functions */
 int GSMTRC_TOTAL ; 
#define  MTRC_TYPE_IGSL 134 
#define  MTRC_TYPE_II32 133 
#define  MTRC_TYPE_IS32 132 
#define  MTRC_TYPE_IU64 131 
#define  MTRC_TYPE_SI32 130 
#define  MTRC_TYPE_SS32 129 
#define  MTRC_TYPE_SU64 128 
 TYPE_2__* gkh_storage ; 

__attribute__((used)) static void *
get_hash (GModule module, GSMetric metric)
{
  void *hash = NULL;
  int i;
  GKHashMetric mtrc;

  for (i = 0; i < GSMTRC_TOTAL; i++) {
    if (hash != NULL)
      break;

    mtrc = gkh_storage[module].metrics[i];
    if (mtrc.metric != metric)
      continue;

    /* Determine the hash structure type */
    switch (mtrc.type) {
    case MTRC_TYPE_II32:
      hash = mtrc.ii32;
      break;
    case MTRC_TYPE_IS32:
      hash = mtrc.is32;
      break;
    case MTRC_TYPE_IU64:
      hash = mtrc.iu64;
      break;
    case MTRC_TYPE_SI32:
      hash = mtrc.si32;
      break;
    case MTRC_TYPE_SS32:
      hash = mtrc.ss32;
      break;
    case MTRC_TYPE_IGSL:
      hash = mtrc.igsl;
      break;
    case MTRC_TYPE_SU64:
      hash = mtrc.su64;
      break;
    }
  }

  return hash;
}