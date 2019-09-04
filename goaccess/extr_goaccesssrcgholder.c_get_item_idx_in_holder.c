#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int idx; TYPE_2__* items; } ;
struct TYPE_6__ {TYPE_1__* metrics; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ GHolder ;

/* Variables and functions */
 int KEY_NOT_FOUND ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_item_idx_in_holder (GHolder * holder, const char *k)
{
  int i;
  if (holder == NULL)
    return KEY_NOT_FOUND;
  if (holder->idx == 0)
    return KEY_NOT_FOUND;
  if (k == NULL || *k == '\0')
    return KEY_NOT_FOUND;

  for (i = 0; i < holder->idx; i++) {
    if (strcmp (k, holder->items[i].metrics->data) == 0)
      return i;
  }

  return KEY_NOT_FOUND;
}