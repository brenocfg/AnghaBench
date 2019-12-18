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
struct attr_item {struct attr_item* next; int /*<<< orphan*/  mode; int /*<<< orphan*/  fname; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct attr_item*) ; 
 int /*<<< orphan*/  setfiletime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void restore_attr(struct attr_item **list)
{
  struct attr_item *item, *prev;

  for (item = *list; item != NULL; )
    {
      setfiletime(item->fname,item->time);
      chmod(item->fname,item->mode);
      prev = item;
      item = item->next;
      free(prev);
    }
  *list = NULL;
}