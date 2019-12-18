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
struct datalink {TYPE_1__* physical; struct datalink* next; } ;
struct bundle {struct datalink* links; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 int /*<<< orphan*/  datalink_Down (struct datalink*,int /*<<< orphan*/ ) ; 

int
bundle_Exception(struct bundle *bundle, int fd)
{
  struct datalink *dl;

  for (dl = bundle->links; dl; dl = dl->next)
    if (dl->physical->fd == fd) {
      datalink_Down(dl, CLOSE_NORMAL);
      return 1;
    }

  return 0;
}