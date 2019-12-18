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
struct TYPE_3__ {int data_len; scalar_t__ delay; } ;
struct TYPE_4__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; TYPE_1__ data; } ;

/* Variables and functions */
 TYPE_2__* current_cache ; 
 int do_pmemcached_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_double_time_since_epoch () ; 

int pmemcached_check_time_current (void) {
  if (current_cache->data.data_len != -1 && current_cache->data.delay >= 0 && current_cache->data.delay < get_double_time_since_epoch()) {
    return do_pmemcached_delete (current_cache->key, current_cache->key_len);
  }
  return 0;
}