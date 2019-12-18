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
struct TYPE_4__ {int size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ GDnsQueue ;

/* Variables and functions */
 scalar_t__ gqueue_empty (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
gqueue_find (GDnsQueue * q, const char *item)
{
  int i;
  if (gqueue_empty (q))
    return 0;

  for (i = 0; i < q->size; i++) {
    if (strcmp (item, q->buffer[i]) == 0)
      return 1;
  }
  return 0;
}