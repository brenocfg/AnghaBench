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
struct TYPE_3__ {int data_len; } ;
struct TYPE_4__ {TYPE_1__ data; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_cache ; 
 scalar_t__ wildcard_engine_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 

int wildcard_report (void) {  
  assert (current_cache->data.data_len != -2);
  if (current_cache->data.data_len >= 0) {
    if (wildcard_engine_report (current_cache->key, current_cache->key_len, current_cache->data) == 0) { return -1; }
  }
  return 0;
}