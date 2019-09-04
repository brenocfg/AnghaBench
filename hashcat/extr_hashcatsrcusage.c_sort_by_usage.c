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
struct TYPE_2__ {scalar_t__ hash_category; scalar_t__ hash_mode; scalar_t__ hash_name; } ;
typedef  TYPE_1__ usage_sort_t ;

/* Variables and functions */
 int strncmp (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int sort_by_usage (const void *p1, const void *p2)
{
  const usage_sort_t *u1 = (const usage_sort_t *) p1;
  const usage_sort_t *u2 = (const usage_sort_t *) p2;

  if (u1->hash_category > u2->hash_category) return  1;
  if (u1->hash_category < u2->hash_category) return -1;

  const int rc_name = strncmp (u1->hash_name + 1, u2->hash_name + 1, 15); // yes, strange...

  if (rc_name > 0) return  1;
  if (rc_name < 0) return -1;

  if (u1->hash_mode > u2->hash_mode) return  1;
  if (u1->hash_mode < u2->hash_mode) return -1;

  return 0;
}