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
struct TYPE_4__ {int nelem; int /*<<< orphan*/ * elems; } ;
typedef  TYPE_1__ position_set ;

/* Variables and functions */

__attribute__((used)) static void
copy (position_set const *src, position_set *dst)
{
  int i;

  for (i = 0; i < src->nelem; ++i)
    dst->elems[i] = src->elems[i];
  dst->nelem = src->nelem;
}