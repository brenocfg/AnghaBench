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
struct TYPE_2__ {scalar_t__ src_len; } ;
typedef  TYPE_1__ keyboard_layout_mapping_t ;

/* Variables and functions */

__attribute__((used)) static int sort_by_src_len (const void *p1, const void *p2)
{
  const keyboard_layout_mapping_t *k1 = (const keyboard_layout_mapping_t *) p1;
  const keyboard_layout_mapping_t *k2 = (const keyboard_layout_mapping_t *) p2;

  return k1->src_len < k2->src_len;
}