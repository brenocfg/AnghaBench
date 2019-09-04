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
struct TYPE_4__ {int text_len; struct TYPE_4__* next; void* text; } ;
typedef  TYPE_1__ black_list ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* bl_head ; 
 int /*<<< orphan*/  black_list_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 void* qmalloc (int) ; 

void black_list_set (char *buf, int len) {
  black_list *cur = bl_head;
  int i, j;
  for (i = 0; i < len; i++) {
    for (j = i; j < len && buf[j] != '\t'; j++) ;
    buf[j] = 0;

    assert (cur->next == NULL);
    cur->next = qmalloc (sizeof (black_list));
    black_list_init (cur->next);
    cur->next->text_len = j - i;
    cur->next->text = qmalloc (j - i + 1);
    memcpy (cur->next->text, buf + i, j - i + 1);
    cur = cur->next;

    i = j;
  }
}