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
struct TYPE_2__ {scalar_t__ offset; } ;
typedef  TYPE_1__ brain_server_attack_short_t ;

/* Variables and functions */

int brain_server_sort_attack_short (const void *v1, const void *v2)
{
  const brain_server_attack_short_t *d1 = (const brain_server_attack_short_t *) v1;
  const brain_server_attack_short_t *d2 = (const brain_server_attack_short_t *) v2;

  if (d1->offset > d2->offset) return  1;
  if (d1->offset < d2->offset) return -1;

  return 0;
}