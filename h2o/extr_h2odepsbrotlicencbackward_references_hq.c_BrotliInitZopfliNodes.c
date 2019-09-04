#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cost; } ;
struct TYPE_5__ {int length; TYPE_1__ u; scalar_t__ insert_length; scalar_t__ distance; } ;
typedef  TYPE_2__ ZopfliNode ;

/* Variables and functions */
 int /*<<< orphan*/  kInfinity ; 

void BrotliInitZopfliNodes(ZopfliNode* array, size_t length) {
  ZopfliNode stub;
  size_t i;
  stub.length = 1;
  stub.distance = 0;
  stub.insert_length = 0;
  stub.u.cost = kInfinity;
  for (i = 0; i < length; ++i) array[i] = stub;
}