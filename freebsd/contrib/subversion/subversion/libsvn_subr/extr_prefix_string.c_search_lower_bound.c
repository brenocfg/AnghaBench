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
struct TYPE_4__ {scalar_t__* data; } ;
struct TYPE_5__ {TYPE_1__ key; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */

__attribute__((used)) static int
search_lower_bound(node_t **sub_nodes,
                   unsigned char key,
                   int count)
{
  int lower = 0;
  int upper = count - 1;

  /* Binary search for the lowest position at which to insert KEY. */
  while (lower <= upper)
    {
      int current = lower + (upper - lower) / 2;

      if ((unsigned char)sub_nodes[current]->key.data[0] < key)
        lower = current + 1;
      else
        upper = current - 1;
    }

  return lower;
}