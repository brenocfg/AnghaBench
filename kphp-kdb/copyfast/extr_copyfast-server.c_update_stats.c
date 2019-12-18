#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__* ints; scalar_t__* longs; scalar_t__* doubles; } ;
union engine_stats {TYPE_3__ arrays; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_13__ {union engine_stats stats; TYPE_1__ node; } ;
struct TYPE_10__ {int* doubles; scalar_t__* ints; scalar_t__* longs; } ;
struct TYPE_12__ {TYPE_2__ arrays; } ;

/* Variables and functions */
 int STATS_DOUBLE_NUM ; 
 int STATS_INT_NUM ; 
 int STATS_LONG_NUM ; 
 TYPE_4__ max_stats ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 TYPE_4__ min_stats ; 
 TYPE_5__* nodes ; 
 int nodes_num ; 
 TYPE_4__ sum_stats ; 
 scalar_t__ total ; 

void update_stats (int use_crc32, int crc32) {
  
  memset (&min_stats, 0x7f, sizeof (union engine_stats));
  memset (&max_stats, 0x80, sizeof (union engine_stats));
  memset (&sum_stats, 0, sizeof (union engine_stats));
  int j;
  total = 0;
  for (j = 0; j < STATS_DOUBLE_NUM; j++) {
    min_stats.arrays.doubles[j] = 1e100;
    max_stats.arrays.doubles[j] = -1e100;
    sum_stats.arrays.doubles[j] = 0;
  }
  for (j = 0; j < nodes_num; j++) if (!use_crc32 || crc32 == (nodes[j].node.id >> 32)){
    union engine_stats* P = &nodes[j].stats;
    int i;
    for (i = 0; i < STATS_INT_NUM; i++) {
      if (min_stats.arrays.ints[i] > P->arrays.ints[i]) {
        min_stats.arrays.ints[i] = P->arrays.ints[i];
      }
      if (max_stats.arrays.ints[i] < P->arrays.ints[i]) {
        max_stats.arrays.ints[i] = P->arrays.ints[i];
      }
      sum_stats.arrays.ints[i] += P->arrays.ints[i];
    }
    for (i = 0; i < STATS_LONG_NUM; i++) {
      if (min_stats.arrays.longs[i] > P->arrays.longs[i]) {
        min_stats.arrays.longs[i] = P->arrays.longs[i];
      }
      if (max_stats.arrays.longs[i] < P->arrays.longs[i]) {
        max_stats.arrays.longs[i] = P->arrays.longs[i];
      }
      sum_stats.arrays.longs[i] += P->arrays.longs[i];
    }
    for (i = 0; i < STATS_DOUBLE_NUM; i++) {
      if (min_stats.arrays.doubles[i] > P->arrays.doubles[i]) {
        min_stats.arrays.doubles[i] = P->arrays.doubles[i];
      }
      if (max_stats.arrays.doubles[i] < P->arrays.doubles[i]) {
        max_stats.arrays.doubles[i] = P->arrays.doubles[i];
      }
      sum_stats.arrays.doubles[i] += P->arrays.doubles[i];
    }
    total ++;
  }
  /*long long *E = (long long *)P;
  int i;
  for (i = 0; i < 21; i++) {
    
  }*/
}