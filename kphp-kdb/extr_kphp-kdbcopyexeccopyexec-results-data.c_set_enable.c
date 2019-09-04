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
struct TYPE_3__ {int disabled; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 TYPE_1__* get_host_by_random_tag (unsigned long long,int /*<<< orphan*/ ) ; 

int set_enable (unsigned long long random_tag, int enable) {
  host_t *H = get_host_by_random_tag (random_tag, 0);
  if (H == NULL) {
    return -1;
  }
  int disabled = enable ? 0 : 1;
  if (H->disabled == disabled) {
    return 1;
  }
  H->disabled = disabled;
  return 0;
}