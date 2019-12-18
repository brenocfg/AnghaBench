#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct points_extra {int points_num; TYPE_2__* points; } ;
struct TYPE_6__ {unsigned long long x; TYPE_3__* B; } ;
typedef  TYPE_2__ rpc_point_t ;
struct TYPE_8__ {int tot_buckets; scalar_t__* extensions_extra; } ;
struct TYPE_7__ {TYPE_1__* methods; } ;
struct TYPE_5__ {scalar_t__ (* get_state ) (TYPE_3__*) ;} ;

/* Variables and functions */
 TYPE_4__* CC ; 
 int MAX_RETRIES ; 
 size_t PE_NUM ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long long crc64 (char*,int) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 

int rpc_points_extension (void **IP, void **Data) {
  char *key = *Data;
  int key_len = (long)*(Data + 1);
  unsigned long long x = crc64 (key, key_len);
  
  rpc_point_t *points = ((struct points_extra *)CC->extensions_extra[PE_NUM])->points;
  int points_num = ((struct points_extra *)CC->extensions_extra[PE_NUM])->points_num;
  
  int a = -1, b = CC->tot_buckets * points_num, c;
  
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (x < points[c].x) {
      b = c;
    } else {
      a = c;
    }
  }

  assert (points_num > 0);

  int i;
  for (i = 0; i < MAX_RETRIES; i++) {
    if (a < 0) {
      a += points_num;
    }
    if (points[a].B->methods->get_state (points[a].B) >= 0) {
      *Data = points[a].B;
      return 0;
    }
    a--;
  }
  *Data = 0;
  return -1;
}