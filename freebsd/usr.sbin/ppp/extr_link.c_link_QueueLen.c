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
struct link {TYPE_1__* Queue; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 unsigned int LINK_QUEUES (struct link*) ; 

size_t
link_QueueLen(struct link *l)
{
  unsigned i;
  size_t len;

  for (i = 0, len = 0; i < LINK_QUEUES(l); i++)
    len += l->Queue[i].len;

  return len;
}