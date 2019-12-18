#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct datalink {unsigned int state; struct datalink* next; } ;
struct bundle {struct datalink* links; } ;

/* Variables and functions */
 unsigned int DATALINK_CLOSED ; 

unsigned
bundle_HighestState(struct bundle *bundle)
{
  struct datalink *dl;
  unsigned result = DATALINK_CLOSED;

  for (dl = bundle->links; dl; dl = dl->next)
    if (result < dl->state)
      result = dl->state;

  return result;
}