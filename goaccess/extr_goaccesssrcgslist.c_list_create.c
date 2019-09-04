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
struct TYPE_4__ {int /*<<< orphan*/ * next; void* data; } ;
typedef  TYPE_1__ GSLList ;

/* Variables and functions */
 TYPE_1__* xmalloc (int) ; 

GSLList *
list_create (void *data)
{
  GSLList *node = xmalloc (sizeof (GSLList));
  node->data = data;
  node->next = NULL;

  return node;
}