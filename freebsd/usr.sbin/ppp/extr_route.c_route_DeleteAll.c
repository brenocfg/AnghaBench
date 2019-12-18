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
struct sticky_route {struct sticky_route* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sticky_route*) ; 

void
route_DeleteAll(struct sticky_route **rp)
{
  struct sticky_route *r, *rn;

  for (r = *rp; r; r = rn) {
    rn = r->next;
    free(r);
  }
  *rp = NULL;
}