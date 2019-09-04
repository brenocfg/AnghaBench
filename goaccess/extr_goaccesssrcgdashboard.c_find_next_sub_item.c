#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_9__ {int next_sub_idx; scalar_t__ look_in_sub; int /*<<< orphan*/  next_parent_idx; int /*<<< orphan*/  next_idx; } ;
struct TYPE_8__ {TYPE_1__* metrics; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_3__* head; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ GSubList ;
typedef  TYPE_3__ GSubItem ;

/* Variables and functions */
 TYPE_4__ find_t ; 
 int regexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_next_sub_item (GSubList * sub_list, regex_t * regex)
{
  GSubItem *iter;
  int i = 0, rc;

  if (sub_list == NULL)
    goto out;

  for (iter = sub_list->head; iter; iter = iter->next) {
    if (i >= find_t.next_sub_idx) {
      rc = regexec (regex, iter->metrics->data, 0, NULL, 0);
      if (rc == 0) {
        find_t.next_idx++;
        find_t.next_sub_idx = (1 + i);
        return 0;
      }
      find_t.next_idx++;
    }
    i++;
  }
out:
  find_t.next_parent_idx++;
  find_t.next_sub_idx = 0;
  find_t.look_in_sub = 0;

  return 1;
}