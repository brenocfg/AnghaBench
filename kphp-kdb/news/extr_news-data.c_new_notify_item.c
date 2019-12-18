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
typedef  int /*<<< orphan*/  notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  items_kept ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zmalloc0 (int) ; 

__attribute__((used)) static notify_t *new_notify_item (void) {
  assert (NOTIFY_MODE);
  items_kept++;
  notify_t *p = zmalloc0 (sizeof (notify_t));
  vkprintf (6, "new_notify_item: result = %p\n", p);
  return p;
}