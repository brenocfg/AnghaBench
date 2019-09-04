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
struct TYPE_2__ {double weight; } ;

/* Variables and functions */
 TYPE_1__* QRW ; 
 int query_rate_weights ; 

__attribute__((used)) static int normalize_query_rate_weights (void) {
  int i;
  double s = 0.0;
  for (i = 0; i < query_rate_weights; i++) {
    s += QRW[i].weight;
  }
  if (s < 1e-9) { return -1; }
  s = 1.0 / s;
  for (i = 0; i < query_rate_weights; i++) {
    QRW[i].weight *= s;
  }
  return 0;
}