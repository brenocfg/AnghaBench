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
struct TYPE_2__ {int weight; } ;

/* Variables and functions */
 TYPE_1__* QRW ; 
 int query_rate_weights ; 

__attribute__((used)) static void rate_weight_clear (int text_weight) {
  QRW[0].weight = text_weight;
  query_rate_weights = 1;
}