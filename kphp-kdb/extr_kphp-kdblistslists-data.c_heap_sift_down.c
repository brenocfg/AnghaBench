#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value_t ;
typedef  int /*<<< orphan*/  global_id_t ;
struct TYPE_3__ {int /*<<< orphan*/  global_id; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* H ; 
 int HN ; 
 scalar_t__ heap_cmp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int heap_sift_down (value_t value, global_id_t  global_id) { 
  int i = 1, j;
  while (1) {
    j = i*2;
    if (j > HN) {
      break;
    }
    if (j < HN && heap_cmp (&H[j+1], H[j].value, H[j].global_id) < 0) {
      j++;
    }
    if (heap_cmp (&H[j], value, global_id) >= 0) {
      break;
    }
    H[i] = H[j];
    i = j;
  }
  return i;
}