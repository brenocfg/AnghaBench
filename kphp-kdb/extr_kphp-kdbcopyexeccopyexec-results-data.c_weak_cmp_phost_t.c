#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ volume_id; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int weak_cmp_phost_t (const host_t *a, const host_t *b) {
  if (a->volume_id < b->volume_id) {
    return -1;
  }
  if (a->volume_id > b->volume_id) {
    return 1;
  }
  return strcmp (a->hostname, b->hostname);
}