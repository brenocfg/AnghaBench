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
struct TYPE_2__ {int pos; } ;
struct iplist {char* src; TYPE_1__ cur; scalar_t__ nItems; } ;

/* Variables and functions */

void
iplist_reset(struct iplist *list)
{
  list->src[0] = '\0';
  list->nItems = 0;
  list->cur.pos = -1;
}