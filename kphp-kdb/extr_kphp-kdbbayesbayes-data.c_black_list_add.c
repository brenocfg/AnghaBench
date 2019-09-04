#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lev_bayes_black_list {scalar_t__ text_len; int type; int /*<<< orphan*/  text; } ;
struct TYPE_5__ {scalar_t__ text_len; void* text; struct TYPE_5__* next; } ;
typedef  TYPE_1__ black_list ;

/* Variables and functions */
 TYPE_1__* bl_head ; 
 int /*<<< orphan*/  black_list_do_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  black_list_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 void* qmalloc (int) ; 
 scalar_t__ strcmp (void*,int /*<<< orphan*/ ) ; 

int black_list_add (struct lev_bayes_black_list *E) {
  black_list *cur = bl_head;
  while (cur->next != NULL && (cur->next->text_len != E->text_len || strcmp (cur->next->text, E->text))) {
    cur = cur->next;
  }

  if (cur->next != NULL) {
    if (E->type & 1) {
      black_list_do_delete (cur);
      return 1;
    } else {
      return 0;
    }
  } else {
    if (E->type & 1) {
      return 0;
    } else {
      cur->next = qmalloc (sizeof (black_list));
      black_list_init (cur->next);
      cur->next->text_len = E->text_len;
      cur->next->text = qmalloc (E->text_len + 1);
      memcpy (cur->next->text, E->text, E->text_len + 1);
      return 1;
    }
  }
}